#ifndef DB_ENGINE_H
#define DB_ENGINE_H

#include <map>
#include <string>
#include <vector>

#include "collection.h"
#include "database.h"
#include "document.h"

class db_engine {
   public:
    // either we can take a path and create databases in that folder,
    // or create a folder named root in the given path and create databases in the new root folder
    // parse root folder and update databases with objects for database, collection and document
    db_engine(std::string root_path);

    // All file operations are handled here.
    // pick a unique id, create object, creates the directory/file
    // returns -1 if exists or invalid name or some other error
    int create_database(std::string name);
    int create_collection(int database_id, std::string name);
    int create_document(int database_id, int collection_id, std::string name);

    // id: name
    std::map<int, std::string> list_databases();

    // what if database_id/collection_id is invalid?
    std::map<int, std::string> list_collections(int database_id);
    std::map<int, std::string> list_documents(int database_id, int collection_id);

    // maybe return pointer
    Database get_database(int database_id);
    Collection get_collection(int database_id, int collection_id);
    Document get_document(int database_id, int collection_id, int document_id);

    // this is also used to update the body after the document is created using create_document
    int update_document(int database_id, int collection_id, int document_id, std::string body);

   private:
    int id;
    std::string root_path;
    std::map<int, Database> databases;
}

#endif