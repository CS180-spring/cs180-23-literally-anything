#include "database.h"
#include <iostream>

using namespace std;

Database::Database(string dbName, string collectionName) {
    this->dbName = dbName;
    this->collectionName = collectionName;

    if (dbName.empty() || collectionName.empty()) {
        cout << "You must enter in a name for the database and a name for the collection!";
    };
}

void Database::add_collection(string collectionName) {
    database.insert({collectionName, Collection(collectionName)});
}

string Database::get_name() {
    return dbName;
}

Collection Database::get_collection(string collectionName) {
    return database[collectionName];
}