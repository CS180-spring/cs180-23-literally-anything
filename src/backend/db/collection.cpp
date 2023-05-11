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
    this->schema = true;
}
string Collection::get_name() {
    return name;
}

void Collection::set_name(string new_name) {
    name = new_name;
}
int Collection::get_id() {
    return id;
}

bool Collection::set_schema(string schema_string) {
    json j = json::parse(schema_string, nullptr, false);

    // Not valid json
    if (j.is_discarded()) {
        return false;
    }

    json_validator validator;

    try {
        validator.set_root_schema(j);
    } catch (const std::exception &e) {
        return false;
    }    
    schema = j;
    return true;
}

string Collection::get_schema() {
    return schema.dump();
}

bool Collection::validate_json(string content) {
    try {
        json_validator validator{schema};
        json j = json::parse(content);
        validator.validate(j); 
    } catch (const std::exception &e) {
        // std::cerr << "Validation failed, here is why: " << e.what() << "\n";
        return false;
    }
    return true;
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

// j is the query inputted by the user
json Collection::search_content_json(json j) {
    json data;
    vector<json> docs;
    bool inDoc = false;
    int numSame = 0;
    for (auto i = documents.begin(); i != documents.end(); i++) {
        // cout << i->first << " " << i->second.get_content_json() << endl;
        numSame = 0;
        data = i->second.get_content_json();
        
        for (auto& el : j.items()) {
            cout << j.size() << endl;
            if (j.size() <= 0 && j.size() == 1) {
                if (data[el.key()] == el.value()) {
                    // inDoc = true;
                    docs.push_back(data);
                    cout << "hello" << endl;
                    
                }
            }
            else {
                if (data[el.key()] == el.value()) {
                    // inDoc = true;
                    cout << "key" << el.key() << endl;
                    numSame++;
                }
                else {
                    // inDoc = false;
                    cout << "numSame: " << numSame << endl;
                    return docs;
                }
            }
            if (numSame == j.size()) {
                cout << "hi" << endl;
                docs.push_back(data);
            }
        }
    }
    return docs;
}

