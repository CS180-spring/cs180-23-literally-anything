#ifndef COLLECTION_H
#define COLLECTION_H
#include <unordered_map>

#include "document.h"
using namespace std;
class Collection {
   public:
    Collection();
    Collection(int id, string name);  // database id
    bool create_document(int id);
    Document& get_document(int id);
    unordered_map<int, Document>& get_documents();
    string get_name();
    int get_id();

   private:
    string name;
    int id;
    unordered_map<int, Document> documents;
};

#endif