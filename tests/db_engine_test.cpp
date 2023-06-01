#include "db_engine.h"

#include <chrono>
#include <climits>
#include <iostream>
#include <string>

#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std::chrono;

int main() {
    DBEngine db_engine("../../tests/test_data");

    // Test db_engine.list_ functions

    // std::cout << "Databases:" << std::endl
    //           << std::endl;
    // std::cout << "Database Name : Database ID" << std::endl;
    // std::cout << "\tCollection Name : Collection ID" << std::endl;
    // std::cout << "\t\t- Document ID" << std::endl;

    // int database_id;
    // std::string database_name;
    // int collection_id;
    // std::string collection_name;
    // int document_id;

    // std::unordered_map<int, std::string> coll_names;

    // std::vector<int> doc_ids;
    // std::unordered_map<int, std::string> db_names = db_engine.list_databases();

    // for (auto const& db_info : db_names) {
    //     Database& db = db_engine.get_database(db_info.first);
    //     database_id = db.get_id();
    //     database_name = db.get_name();
    //     coll_names = db_engine.list_collections(database_id);

    //     std::cout << "\n"
    //               << database_name << " : " << database_id << std::endl;

    //     for (auto const& coll_info : coll_names) {
    //         Collection& coll = db_engine.get_collection(database_id, coll_info.first);
    //         collection_id = coll.get_id();
    //         collection_name = coll.get_name();

    //         std::cout << "\t" << collection_name << " : " << collection_id << std::endl;
    //         doc_ids = db_engine.list_documents(database_id, collection_id);

    //         for (auto const& doc_id_entry : doc_ids) {
    //             Document& doc = db_engine.get_document(database_id, collection_id, doc_id_entry);
    //             document_id = doc.get_id();
    //             std::cout << "\t\t- " << document_id << std::endl;
    //         }
    //     }
    // }

    // Test get_document and creating new db/coll/docs
    // Document& doc = db_engine.get_document(123, 345, 999);
    // std::cout << "\nContent of document: 123/345/999.json\n"
    //           << doc.get_content() << std::endl;

    int db_id = db_engine.create_database("Example Database");
    int db_id2 = db_engine.create_database("Example Database 1");

    Database& dbb = db_engine.get_database(db_id);
    std::cout << "\ndb: " << dbb.get_name() << std::endl;
    std::cout << "\ndb id: " << dbb.get_id() << std::endl;

    int coll_id = db_engine.create_collection(db_id, "Example Collection");
    int coll_id2 = db_engine.create_collection(db_id, "Example Collection");
    int coll_id3 = db_engine.create_collection(db_id, "Example Collection");
    int coll_id4 = db_engine.create_collection(db_id2, "Example Collection");
    int coll_id5 = db_engine.create_collection(db_id2, "Example Collection");

    int status;
    Collection& colll = db_engine.get_collection(db_id, coll_id, status);
    std::cout << "colll: " << colll.get_name() << std::endl;
    std::cout << "coll id: " << colll.get_id() << std::endl;

    db_engine.create_document(db_id, coll_id);
    db_engine.create_document(db_id, coll_id2);
    db_engine.create_document(db_id, coll_id3);
    db_engine.create_document(db_id2, coll_id4);
    db_engine.create_document(db_id2, coll_id5);
    db_engine.create_document(db_id2, coll_id4);
    db_engine.create_document(db_id2, coll_id5);
    db_engine.create_document(db_id, coll_id);
    db_engine.create_document(db_id, coll_id2);
    db_engine.create_document(db_id, coll_id3);
    db_engine.create_document(db_id2, coll_id4);
    db_engine.create_document(db_id2, coll_id5);

    int doc_id = db_engine.create_document(db_id, coll_id);
    Document& docc = db_engine.get_document(db_id, coll_id, doc_id);
    std::cout << "docc: " << docc.get_id() << std::endl;



    // Test Schema Validator
    
    json schema = json::parse(R"(
        {
            "$schema": "http://json-schema.org/draft-04/schema#",
            "type": "object",
            "properties": {
                "pi": {
                "type": "number"
                },
                "happy": {
                "type": "boolean"
                }
            },
            "required": [
                "pi",
                "happy"
            ]
        }
        )");
    // json schema = {}; 
    json j2 = {
        {"pi", 3.141},
        {"happy", true},
        {"name", "Niels"},
        {"nothing", nullptr},
        {"answer", {{"everything", 42}}},
        {"list", {1, 0, 2}},
        {"object", {{"currency", "USD"}, {"value", 42.99}}}
        };

    
    int valid_schema = db_engine.set_collection_schema(db_id, coll_id, schema.dump());
    std::cout << "Valid Schema? " << valid_schema << std::endl;

    int valid_doc = db_engine.update_document(db_id, coll_id, doc_id, j2.dump());
    std::cout << "Valid Document? " << valid_doc << std::endl;
    std::string bodyy; 
    status = db_engine.get_document_body(db_id, coll_id, doc_id, bodyy);
    std::cout << "body:\n"
              << json::parse(bodyy).dump(2) << std::endl;

    // testing delete database
    // db_engine.delete_database(db_id);
    // cout << db_engine.get_database(db_id).get_name() << endl;
    json jtest1 = {{"name", "Niels"}, {"happy", true}};
    json search = colll.search_content_json(jtest1);
    json jtest2 = {{"pi", 3.141}};
    json jtest3 = {{"happy", true}};     
    std::cout << "Searching name: Niels, and happy: true search result:" << search.dump(2) << std::endl;     
    json search2 = colll.search_content_json(jtest2);     
    std::cout << "Searching name: pi 3.141, search result::" << search2.dump(2) << std::endl;
    json jtest4 = {{"name", "Niels"}, {"happy", false}};
    json search3 = colll.search_content_json(jtest4);
    std::cout << "Searching name: Niels, and happy: false search result:" << search3.dump(2) << std::endl;   
    json jtest5 = {{"name", "Alex"}, {"happy", false}};
    json search4 = colll.search_content_json(jtest5);
    std::cout << "Searching name: Alex, and happy: false search result:" << search4.dump(2) << std::endl;   

    // testing count
    cout << "Num collections: " << db_engine.get_num_collections(19524072) << endl;
    cout << "Num documents: " << db_engine.get_num_docs(19524072, 20422072) << endl;
   
    return 0;
}