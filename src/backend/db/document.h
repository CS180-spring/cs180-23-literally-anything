#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

class Document {
   public:
    Document();
    Document(int id);
    int get_id();
    std::string get_content();
    bool update_content(std::string content);

   private:
    int id;

    // this will be a json object in the future
    std::string body;
};

#endif