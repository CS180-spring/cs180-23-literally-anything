#ifndef DB_ENGINE_H
#define DB_ENGINE_H

#include <string>
#include <unordered_map>
#include <vector>

#include "collection.h"
#include "database.h"
#include "document.h"

class DBEngine {
   public:
    // either we can take a path and create databases in that folder,
    // or create a folder named root in the given path and create databases in the new root folder
    // parse root folder and update databases with objects for database, collection and document
    DBEngine();
    DBEngine(std::string root_path);

    // All file operations are handled here.
    // pick a unique id, create object, creates the directory/file
    // returns -1 if exists or invalid name or some other error
    int create_database(std::string name);
    int create_collection(int database_id, std::string name);
    int create_document(int database_id, int collection_id);

    // what if database_id/collection_id is invalid?
    std::unordered_map<int, std::string> list_databases();
    std::unordered_map<int, std::string> list_collections(int database_id);
    std::vector<int> list_documents(int database_id, int collection_id);

    std::string get_document_body(int database_id, int collection_id, int document_id);

    // maybe return pointer
    Database& get_database(int database_id);
    Collection& get_collection(int database_id, int collection_id);
    Document& get_document(int database_id, int collection_id, int document_id);

    std::unordered_map<int, Database> get_databases();
    std::unordered_map<int, Collection> get_collections(int database_id);
    std::unordered_map<int, Document> get_documents(int database_id, int collection_id);

    // this is also used to update the body after the document is created using create_document
    int update_document(int database_id, int collection_id, int document_id, std::string body);
    int delete_database(int id);

   private:
    std::string root_path;
    std::unordered_map<int, Database> databases;
};

#endif