#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

#include "collection.h"

class Database {
   public:
    Database();
    Database(int id, string name);                // database id
    bool create_collection(int id, string name);  //  collection id
    Collection& get_collection(int id);
    unordered_map<int, Collection>& get_collections();
    string get_name();
    int get_id();

   private:
    string name;
    int id;
    unordered_map<int, Collection> collections;
};

#endif