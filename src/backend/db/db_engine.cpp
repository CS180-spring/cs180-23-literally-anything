#include "db_engine.h"

#include <chrono>
#include <climits>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std::chrono;
#include "../../../include/nlohmann/json.hpp"
using json = nlohmann::json;


DBEngine::DBEngine() { int a = 1; }
DBEngine::DBEngine(std::string root_path) {
    // create root directory in the given path root_path/root
    root_path = root_path.append("/root");
    const std::filesystem::path root{root_path};
    std::filesystem::create_directory(root);

    this->root_path = root_path;
    // traverse root_path

    std::string dir_name;
    int dir_id;
    std::string db_info_path;
    json db_info;
    std::unordered_map<int, Database>::iterator db_it;

    std::string coll_dir_name;
    int coll_dir_id;
    std::string coll_info_path;
    json coll_info;

    std::string doc_file_name;
    int doc_file_id;
    std::string doc_file_contents;

    for (std::filesystem::directory_entry const& dir_entry : std::filesystem::directory_iterator{root}) {
        if (dir_entry.is_directory() == true) {
            dir_name = dir_entry.path().filename();
            dir_id = std::stoi(dir_name);
            db_info_path = dir_entry.path() / "db.json";
            std::ifstream db_info_file(db_info_path);
            db_info = json::parse(db_info_file);
            databases.insert({dir_id, Database(db_info["id"].get<int>(), db_info["name"].get<std::string>())});

            Database& db = databases[dir_id];
            // traverse through the database folder
            // and create collections for each
            for (std::filesystem::directory_entry const& coll_dir_entry : std::filesystem::directory_iterator{dir_entry.path()}) {
                if (coll_dir_entry.is_directory() == true) {
                    coll_dir_name = coll_dir_entry.path().filename();
                    coll_dir_id = std::stoi(coll_dir_name);
                    coll_info_path = coll_dir_entry.path() / "collection.json";
                    std::ifstream coll_info_file(coll_info_path);
                    coll_info = json::parse(coll_info_file);
                    db.create_collection(coll_info["id"].get<int>(), coll_info["name"].get<std::string>());
                    Collection& coll = db.get_collection(coll_dir_id);

                    for (std::filesystem::directory_entry const& doc_file_entry : std::filesystem::directory_iterator{coll_dir_entry.path()}) {
                        if ((doc_file_entry.is_directory() == false) && (doc_file_entry.path().filename() != "collection.json")) {
                            doc_file_name = doc_file_entry.path().filename();
                            doc_file_id = stoi(doc_file_name);
                            std::ifstream doc_file(doc_file_entry.path());
                            std::stringstream buffer;
                            buffer << doc_file.rdbuf();
                            coll.create_document(doc_file_id);
                            Document& doc = coll.get_document(doc_file_id);
                            doc.update_content(buffer.str());
                        }
                    }
                }
            }
        }
    }
}

// not used
std::unordered_map<int, Database> DBEngine::get_databases() {
    return databases;
}

// not used
std::unordered_map<int, Collection> DBEngine::get_collections(int database_id) {
    Database db = databases[database_id];
    return db.get_collections();
}

// not used
std::unordered_map<int, Document> DBEngine::get_documents(int database_id, int collection_id) {
    Database db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);

    return coll.get_documents();
}

// not used
Database& DBEngine::get_database(int database_id) {
    // add logic if database_id does note exist
    return databases[database_id];
}

Collection& DBEngine::get_collection(int database_id, int collection_id, int& valid) {
    if (databases.find(database_id) == databases.end()) {
        // Database does not exist
        valid = -1;
    }
    unordered_map<int, Collection> &collections = databases[database_id].get_collections();

    if (collections.find(collection_id) == collections.end()) {
        // Collection does not exist
        valid = -2;
    }
    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);
    valid = 0;
    return coll;
}

// not used
Document& DBEngine::get_document(int database_id, int collection_id, int document_id) {
    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);
    Document& doc = coll.get_document(document_id);
    return doc;
}

int DBEngine::get_document_body(int database_id, int collection_id, int document_id, string& body) {
    if (databases.find(database_id) == databases.end()) {
        // Database does not exist
        return -1;
    }
    Database& db = databases[database_id];
    unordered_map<int, Collection> &collections = db.get_collections();

    if (collections.find(collection_id) == collections.end()) {
        // Collection does not exist
        return -2;
    }
    Collection& coll = db.get_collection(collection_id);
    unordered_map<int, Document> &documents = coll.get_documents();

    if (documents.find(document_id) == documents.end()) {
        // Document does not exist
        return -3;
    }

    Document& doc = coll.get_document(document_id);
    std::string content = doc.get_content();

    body = content;
    return 0;
}

int DBEngine::update_document(int database_id, int collection_id, int document_id, std::string body) {
    if (databases.find(database_id) == databases.end()) {
        // Database does not exist
        return -4;
    }
    Database& db = databases[database_id];
    unordered_map<int, Collection> &collections = db.get_collections();

    if (collections.find(collection_id) == collections.end()) {
        // Collection does not exist
        return -5;
    }
    Collection& coll = db.get_collection(collection_id);
    unordered_map<int, Document> &documents = coll.get_documents();

    if (documents.find(document_id) == documents.end()) {
        // Document does not exist
        return -6;
    }

    json j = json::parse(body, nullptr, false);

    // Not valid json
    if (j.is_discarded()) {
        return -1;
    }

    Document& doc = coll.get_document(document_id);

    
    // Check if json matches schema for colection
    bool valid = coll.validate_json(body);
    if (!valid) {
        return -2;
    }

    bool updated = doc.update_content(body);

    if (!updated) {
        return -3;
    }

    // update file system
    std::string path = root_path + "/" + std::to_string(database_id) + "/" + std::to_string(collection_id) + "/" + std::to_string(document_id) + ".json";
    std::ofstream out(path);
    out << body;
    out.close();
    return 0;
}

int DBEngine::create_database(std::string name) {
    int id = duration_cast<nanoseconds>(
                 system_clock::now().time_since_epoch())
                 .count() &
             INT_MAX;
    databases.insert({id, Database(id, name)});

    json db_info;
    db_info["id"] = id;
    db_info["name"] = name;
    std::string db_info_str = db_info.dump(4);
    std::string db_path = root_path + "/" + std::to_string(id);
    std::filesystem::create_directory(db_path);
    db_path = root_path + "/" + std::to_string(id) + "/db.json";
    std::ofstream out(db_path);
    out << db_info_str;
    out.close();

    return id;
}

int DBEngine::create_collection(int database_id, std::string name) {
    if (databases.find(database_id) == databases.end()) {
        // Database does not exist
        return -1;
    }
    int id = duration_cast<nanoseconds>(
                 system_clock::now().time_since_epoch())
                 .count() &
             INT_MAX;
    Database& db = databases[database_id];
    db.create_collection(id, name);

    json coll_info;
    coll_info["id"] = id;
    coll_info["name"] = name;
    std::string coll_info_str = coll_info.dump(4);
    std::string coll_path = root_path + "/" + std::to_string(database_id) + "/" + std::to_string(id);
    std::filesystem::create_directory(coll_path);
    coll_path = root_path + "/" + std::to_string(database_id) + "/" + std::to_string(id) + "/collection.json";
    std::ofstream out(coll_path);
    out << coll_info_str;
    out.close();

    return id;
}

int DBEngine::create_document(int database_id, int collection_id) {
    if (databases.find(database_id) == databases.end()) {
        // Database does not exist
        return -1;
    }
    unordered_map<int, Collection> &collections = databases[database_id].get_collections();

    if (collections.find(collection_id) == collections.end()) {
        // Collection does not exist
        return -2;
    }

    int id = duration_cast<nanoseconds>(
                 system_clock::now().time_since_epoch())
                 .count() &
             INT_MAX;

    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);
    coll.create_document(id);

    std::string path = root_path + "/" + std::to_string(database_id) + "/" + std::to_string(collection_id) + "/" + std::to_string(id) + ".json";
    std::ofstream{path};

    return id;
}

int DBEngine::set_collection_schema(int database_id, int collection_id, std::string schema) {
    if (databases.find(database_id) == databases.end()) {
        // Database does not exist
        return -2;
    }
    unordered_map<int, Collection> &collections = databases[database_id].get_collections();

    if (collections.find(collection_id) == collections.end()) {
        // Collection does not exist
        return -3;
    }

    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);

    bool valid = coll.set_schema(schema);
    if (!valid) return -1;

    // TODO: update schema in filsystem
    return 0;
}

int DBEngine::get_collection_schema(int database_id, int collection_id, string& schema) {
    if (databases.find(database_id) == databases.end()) {
        // Database does not exist
        return -1;
    }
    unordered_map<int, Collection> &collections = databases[database_id].get_collections();

    if (collections.find(collection_id) == collections.end()) {
        // Collection does not exist
        return -2;
    }

    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);

    schema = coll.get_schema();
    return 0;
}

std::unordered_map<int, std::string> DBEngine::list_databases() {
    std::unordered_map<int, std::string> db_names;
    for (auto const& db_entry : databases) {
        Database db = db_entry.second;
        db_names.insert({db.get_id(), db.get_name()});
    }

    return db_names;
}

int DBEngine::list_collections(int database_id, std::unordered_map<int, std::string>& coll_names) {
    if (databases.find(database_id) == databases.end()) {
        // Database does not exist
        return -1;
    }
    // std::unordered_map<int, std::string> coll_names;
    Database& db = databases[database_id];

    unordered_map<int, Collection>& collections = db.get_collections();
    for (auto & coll_entry : collections) {
        Collection& coll = coll_entry.second;
        coll_names.insert({coll.get_id(), coll.get_name()});
    }

    // return coll_names;
    return 0;
}

// returns vector of document ids
int DBEngine::list_documents(int database_id, int collection_id, std::vector<int>& doc_names) {
    if (databases.find(database_id) == databases.end()) {
        // Database does not exist
        return -1;
    }
    unordered_map<int, Collection> &collections = databases[database_id].get_collections();

    if (collections.find(collection_id) == collections.end()) {
        // Collection does not exist
        return -2;
    }

    // std::vector<int> doc_names;
    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);

    unordered_map<int, Document>& documents = coll.get_documents();
    for (auto const& doc_entry : documents) {
        Document doc = doc_entry.second;
        doc_names.push_back(doc.get_id());
    }

    // return doc_names;
    return 0;
}

// Success: 0
// Invalid DB id: -2
int DBEngine::delete_database(int id) {
    if (databases.find(id) == databases.end()) {
        // Database does not exist
        return -1;
    }

    std::string path = root_path + "/" + std::to_string(id);
    if (std::filesystem::exists(path)) {
        databases.erase(id);
        std::filesystem::remove_all(path);
    }
    else {
        return -2;
    }
    return 0;
}

int DBEngine::delete_collection(int db_id, int coll_id) {
    if (databases.find(db_id) == databases.end()) {
        // Database does not exist
        return -1;
    }
    unordered_map<int, Collection> &collections = databases[db_id].get_collections();

    if (collections.find(coll_id) == collections.end()) {
        // Collection does not exist
        return -2;
    }

    std::string path = root_path + "/" + std::to_string(db_id) + "/" + std::to_string(coll_id);
    if (std::filesystem::exists(path)) {
        collections.erase(coll_id);
        std::filesystem::remove_all(path);
    }
    else {
        return -3;
    }
    return 0;
}

int DBEngine::delete_document(int db_id, int coll_id, int doc_id) {
    if (databases.find(db_id) == databases.end()) {
        // Database does not exist
        return -1;
    }
    unordered_map<int, Collection> &collections = databases[db_id].get_collections();

    if (collections.find(coll_id) == collections.end()) {
        // Collection does not exist
        return -2;
    }
    Collection& coll = collections[coll_id];
    unordered_map<int, Document> &documents = coll.get_documents();

    if (documents.find(doc_id) == documents.end()) {
        // Document does not exist
        return -3;
    }
    documents.erase(doc_id);

    std::string path = root_path + "/" + std::to_string(db_id) + "/" + std::to_string(coll_id) + "/" + std::to_string(doc_id) + ".json";

    if (std::filesystem::exists(path)) {
        std::filesystem::remove_all(path);
    }
    else {
        return -4;
    }
    return 0;
}

int DBEngine::get_num_collections(int db_id) {
    int count = 0;
    unordered_map<int, Collection> &collections = databases[db_id].get_collections();

    for (auto i = collections.begin(); i != collections.end(); i++) {
        count++;
    }

    return count;
}

int DBEngine::get_num_docs(int db_id, int coll_id) {
    int count = 0;
    auto x = databases[db_id].get_collection(coll_id);
    unordered_map<int, Document> &documents = x.get_documents();

    for (auto i = documents.begin(); i != documents.end(); i++) {
        count++;
    }

    return count;

}
