#ifndef DATABASE_H
#define DATABASE_H
#include "collection.h"
using namespace std;

class Database {
    public:
        Database();
        Database(int id, string dbName, string collectionName);
        // bool create_collection(int id, string collectionName);
        string get_name();
        Collection get_collection(int id);
        map<int, Collection> get_collections();
        int get_id();

    private:
        string dbName;
        string collectionName;
        int id;
        map<int, Collection> collections;
};

#endif