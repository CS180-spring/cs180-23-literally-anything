#include "database.h"
#include <iostream>

using namespace std;

Database::Database() {
    this->id = 9999;
    this->dbName = "default db";
    this->collectionName = "default collection";
}

Database::Database(int id, string dbName, string collectionName) {
    this->id = id;
    this->dbName = dbName;
    this->collectionName = collectionName;
}

// bool Database::create_collection(int id, string collectionName) {
//     collections.insert({id, Collection(id, collectionName)});
//     return 1;
// }

string Database::get_name() {
    return dbName;
}

Collection& Database::get_collection(int id) {
    return collections[id];
}

map<int, Collection>& Database::get_collections() {
    return collections;
}

int Database::get_id() {
    return id;
}