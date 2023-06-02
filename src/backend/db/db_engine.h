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
    DBEngine();
    DBEngine(std::string root_path);

    int create_database(std::string name);
    int create_collection(int database_id, std::string name);
    int create_document(int database_id, int collection_id);

    std::unordered_map<int, std::string> list_databases();
    int list_collections(int database_id, std::unordered_map<int, std::string>& coll_names);
    int list_documents(int database_id, int collection_id, std::vector<int>& doc_names);

    int set_collection_schema(int database_id, int collection_id, std::string schema);
    int get_collection_schema(int database_id, int collection_id, std::string& schema);
    int get_document_body(int database_id, int collection_id, int document_id, std::string& body);

    Database& get_database(int database_id);
    Collection& get_collection(int database_id, int collection_i, int& valid);
    Document& get_document(int database_id, int collection_id, int document_id);

    std::unordered_map<int, Database> get_databases();
    std::unordered_map<int, Collection> get_collections(int database_id);
    std::unordered_map<int, Document> get_documents(int database_id, int collection_id);

    int update_document(int database_id, int collection_id, int document_id, std::string body);

    int delete_database(int id);
    int delete_collection(int db_id, int coll_id);
    int delete_document(int db_id, int coll_id, int doc_id);
    int get_num_collections(int db_id);
    int get_num_docs(int db_id, int coll_id);
    
   private:
    std::string root_path;
    std::unordered_map<int, Database> databases;
};

#endif