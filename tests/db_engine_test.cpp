#include "../src/backend/db/db_engine.h"

#include <chrono>
#include <climits>
#include <iostream>
#include <string>
using namespace std::chrono;

int main() {
    DBEngine db_engine("./test_data");

    // Test db_engine.list_ functions

    std::cout << "Databases:" << std::endl
              << std::endl;
    std::cout << "Database Name : Database ID" << std::endl;
    std::cout << "\tCollection Name : Collection ID" << std::endl;
    std::cout << "\t\t- Document ID" << std::endl;

    int database_id;
    std::string database_name;
    int collection_id;
    std::string collection_name;
    int document_id;

    std::map<int, std::string> coll_names;

    std::vector<int> doc_ids;
    std::map<int, std::string> db_names = db_engine.list_databases();

    for (auto const& db_info : db_names) {
        Database& db = db_engine.get_database(db_info.first);
        database_id = db.get_id();
        database_name = db.get_name();
        coll_names = db_engine.list_collections(database_id);

        std::cout << "\n"
                  << database_name << " : " << database_id << std::endl;

        for (auto const& coll_info : coll_names) {
            Collection& coll = db_engine.get_collection(database_id, coll_info.first);
            collection_id = coll.get_id();
            collection_name = coll.get_name();

            std::cout << "\t" << collection_name << " : " << collection_id << std::endl;
            doc_ids = db_engine.list_documents(database_id, collection_id);

            for (auto const& doc_id_entry : doc_ids) {
                Document& doc = db_engine.get_document(database_id, collection_id, doc_id_entry);
                document_id = doc.get_id();
                std::cout << "\t\t- " << document_id << std::endl;
            }
        }
    }

    // Test get_document and creating new db/coll/docs
    Document& doc = db_engine.get_document(123, 345, 999);
    std::cout << "\nContent of document: 123/345/999.json\n"
              << doc.get_content() << std::endl;

    int db_id = db_engine.create_database("oiasdjiaosd");
    Database& dbb = db_engine.get_database(db_id);
    std::cout << "\ndb: " << dbb.get_name() << std::endl;

    int coll_id = db_engine.create_collection(db_id, "asdaisd");
    Collection& colll = db_engine.get_collection(db_id, coll_id);
    std::cout << "colll: " << colll.get_name() << std::endl;
    std::cout << "coll id: " << colll.get_id() << std::endl;

    int doc_id = db_engine.create_document(db_id, coll_id);
    Document& docc = db_engine.get_document(db_id, coll_id, doc_id);
    std::cout << "docc: " << docc.get_id() << std::endl;

    db_engine.update_document(db_id, coll_id, doc_id, "ajisodjaoisjdoiajsodiaoisjdoasjd");
    std::string bodyy = db_engine.get_document_body(db_id, coll_id, doc_id);
    std::cout << "body:\n"
              << bodyy << std::endl;

    return 0;
}