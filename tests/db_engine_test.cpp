#include "../src/backend/db/db_engine.h"

#include <iostream>
#include <string>

int main() {
    DBEngine db_engine("../data");

    std::map<int, Database> databases = db_engine.get_databases();

    for (auto const& db_entry : databases) {
        Database db = db_entry.second;
        cout << "DB id: " << db_entry.first << " name: " << db.get_name() << std::endl;
    }

    std::string text = db_engine.get_document_body(123, 345, 999);

    std::cout << "out: " << text << std::endl;
    return 0;
}