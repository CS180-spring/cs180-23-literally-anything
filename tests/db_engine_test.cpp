#include "../src/backend/db/db_engine.h"

#include <chrono>
#include <climits>
#include <iostream>
#include <string>
using namespace std::chrono;

int main() {
    DBEngine db_engine("../data");

    std::map<int, Database> databases = db_engine.get_databases();

    for (auto const& db_entry : databases) {
        Database db = db_entry.second;
        cout << "DB id: " << db_entry.first << " name: " << db.get_name() << std::endl;
    }

    Document& doc = db_engine.get_document(123, 345, 999);

    std::cout << "Content of document: \n"
              << doc.get_content() << std::endl;

    int db_id = db_engine.create_database("oiasdjiaosd");
    Database& dbb = db_engine.get_database(db_id);
    std::cout << "db: " << dbb.get_name() << std::endl;

    int coll_id = db_engine.create_collection(db_id, "asdaisd");
    Collection& colll = db_engine.get_collection(db_id, coll_id);
    std::cout << "colll: " << colll.get_name() << std::endl;
    std::cout << "coll id: " << colll.get_id() << std::endl;

    int doc_id = db_engine.create_document(db_id, coll_id);
    Document& docc = db_engine.get_document(db_id, coll_id, doc_id);
    std::cout << "docc: " << docc.get_id() << std::endl;

    db_engine.update_document(db_id, coll_id, doc_id, "ajisodjaoisjdoiajsodiaoisjdoasjd");
    std::string bodyy = db_engine.get_document_body(db_id, coll_id, doc_id);
    std::cout << "body:\n " << bodyy << std::endl;

    return 0;
}