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
// bool Collection::create_document(int id) {
//     Document temp = Document(id);
//     documents.insert({id, temp});
//     return true;
// }
Document& Collection::get_document(int id) {
    return documents[id];
}

map<int, Document>& Collection::get_documents() {
    return documents;
}

string Collection::get_name() {
    return name;
}

int Collection::get_id() {
    return id;
}