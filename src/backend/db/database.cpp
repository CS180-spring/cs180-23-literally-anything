#include "database.h"

#include <iostream>
using namespace std;
Database::Database() {
    this->name = "default_db";
    this->id = 99999;
}
Database::Database(int id, string name) {
    this->name = name;
    this->id = id;
}
bool Database::create_collection(int id, string name) {
    collections.insert({id, Collection(id, name)});
    return 1;
}
Collection& Database::get_collection(int id) {
    return collections[id];
}

map<int, Collection>& Database::get_collections() {
    return collections;
}

string Database::get_name() {
    return name;
}

int Database::get_id() {
    return id;
}