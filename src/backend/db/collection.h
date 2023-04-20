#ifndef COLLECTION_H
#define COLLECTION_H
#include <map>

#include "document.h"
using namespace std;
class Collection {
   public:
    Collection();
    Collection(int id, string name);  // database id
    bool create_document(int id);     // document id
    Document get_document(int id);
    map<int, Document> get_documents();
    string get_name();
    int get_id();

   private:
    string name;
    int id;
    map<int, Document> documents;
};

#endif