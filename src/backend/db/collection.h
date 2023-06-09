#ifndef COLLECTION_H
#define COLLECTION_H
#include <unordered_map>
#include <vector>
#include "nlohmann/json-schema.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
#include "document.h"

using json_validator = nlohmann::json_schema::json_validator;

using namespace std;
class Collection {
   public:
    Collection();
    Collection(int id, string name);
    string get_name();
    void set_name(string new_name);
    int get_id();
    bool set_schema(string schema_string);
    string get_schema();
    bool validate_json(string content);
    bool create_document(int id);
    Document& get_document(int id);
    unordered_map<int, Document>& get_documents();
    vector<json> search_content_json(json j);

   private:
    int id;
    string name;
    json schema;
    unordered_map<int, Document> documents;
};

#endif