#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class Document {
   public:
    Document();
    Document(int id);
    int get_id();
    std::string get_content();
    json get_content_json();
    bool update_content(std::string content);

   private:
    int id;
    std::string content_str;
    json content;
};

#endif