#ifndef COLLECTION_H
#define COLLECTION_H
#include <map>
#include "document.h"
using namespace std;
class Collection {
    public:
    Collection(string name); //database id
    void add_document(int id); //document id
    Document get_document(int id);
    string get_name();

    private:
    string name;
    map<int,Document> collection;
};


#endif