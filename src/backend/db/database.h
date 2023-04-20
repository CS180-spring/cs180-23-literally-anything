#ifndef DATABASE_H
#define DATABASE_H
#include "collection.h"
using namespace std;

class Database {
    public:
        Database(string dbName, string collectionName);
        void add_collection(string collectionName);
        string get_name();
        Collection get_collection(string collectionName);

        private:
            string dbName;
            string collectionName;
            map<string, Collection> database;
};

#endif