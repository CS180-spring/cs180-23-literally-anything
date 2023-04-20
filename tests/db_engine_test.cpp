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

    Document& doc = db_engine.get_document(123, 345, 999);

    std::cout << "out: " << doc.get_content() << std::endl;
    return 0;
}