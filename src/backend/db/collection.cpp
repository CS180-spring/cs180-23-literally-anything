#include "collection.h"

#include <iostream>
using namespace std;
Collection::Collection() {
    this->name = "default collection";
    this->id = 9999;
}
Collection::Collection(int id, string name) {
    this->name = name;
    this->id = id;
}
bool Collection::create_document(int id) {
    documents.insert({id, Document(id)});
    return 1;
}
Document& Collection::get_document(int id) {
    return documents[id];
}

unordered_map<int, Document>& Collection::get_documents() {
    return documents;
}

string Collection::get_name() {
    return name;
}

int Collection::get_id() {
    return id;
}

void Collection::delete_document(int id) {
    documents.erase(id);
}