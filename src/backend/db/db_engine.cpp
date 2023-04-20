#include "db_engine.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <chrono>
#include <climits>
using namespace std::chrono;
#include "../../../include/nlohmann/json.hpp"
using json = nlohmann::json;

DBEngine::DBEngine() {int a = 1;}
DBEngine::DBEngine(std::string root_path) {
    // create root directory in the given path root_path/root
    root_path = root_path.append("/root");
    const std::filesystem::path root{root_path};
    std::filesystem::create_directory(root);

    // traverse root_path

    std::string dir_name;
    int dir_id;
    std::string db_info_path;
    json db_info;
    std::map<int, Database>::iterator db_it;

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

            // dir_id should == db_info["id"].get<int>()
            db_it = databases.find(dir_id);
            if (db_it == databases.end()) {
                // didnt get added or ma
                int aasd;
            } else {
                Database& db = db_it->second;
                // traverse through the database folder
                // and create collections for each
                for (std::filesystem::directory_entry const& coll_dir_entry : std::filesystem::directory_iterator{dir_entry.path()}) {
                    if (coll_dir_entry.is_directory() == true) {
                        coll_dir_name = coll_dir_entry.path().filename();
                        coll_dir_id = std::stoi(coll_dir_name);
                        coll_info_path = coll_dir_entry.path() / "collection.json";
                        std::ifstream coll_info_file(coll_info_path);
                        coll_info = json::parse(coll_info_file);
                        db.create_collection(db_info["id"].get<int>(), db_info["name"].get<std::string>());
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
}

std::map<int, Database> DBEngine::get_databases() {
    return databases;
}

std::map<int, Collection> DBEngine::get_collections(int database_id) {
    Database db = databases[database_id];
    return db.get_collections();
}

std::map<int, Document> DBEngine::get_documents(int database_id, int collection_id) {
    Database db = databases[database_id];
    Collection coll = db.get_collection(collection_id);

    return coll.get_documents();
}

Database& DBEngine::get_database(int database_id) {
    // add logic if database_id does note exist
    return databases[database_id];
}

Collection& DBEngine::get_collection(int database_id, int collection_id) {
    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);
    return coll;
}

Document& DBEngine::get_document(int database_id, int collection_id, int document_id) {
    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);
    Document& doc = coll.get_document(document_id);
    return doc;
}

std::string DBEngine::get_document_body(int database_id, int collection_id, int document_id) {
    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);
    Document& doc = coll.get_document(document_id);
    std::string content = doc.get_content();
    return content;
}


int DBEngine::update_document(int database_id, int collection_id, int document_id, std::string body) {
    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);
    Document& doc = coll.get_document(document_id);
    doc.update_content(body);

    // update file system
    std::string path = root_path + "/" + std::to_string(database_id) + "/" + std::to_string(collection_id) + "/" + std::to_string(document_id) + ".json";
    std::ofstream out(path);
    out << body;
    out.close();
    return 0;
}

int DBEngine::create_database(std::string name) {
    int id = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()).count() & INT_MAX;
    databases.insert({id,  Database(id, name)});
    return id;
    }

int DBEngine::create_collection(int database_id, std::string name) {
    int id = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()).count() & INT_MAX;
    Database& db = databases[database_id];
    db.create_collection(id, name);

    return id;
}

int DBEngine::create_document(int database_id, int collection_id) {
    int id = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()).count() & INT_MAX;
    Database& db = databases[database_id];
    Collection& coll = db.get_collection(collection_id);
    coll.create_document(id);

    return id;
}