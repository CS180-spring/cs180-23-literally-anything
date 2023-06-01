#include "crow.h"
#include "../db/db_engine.h"

#include "../../../include/nlohmann/json.hpp"
using json = nlohmann::json;

#include <sstream>
#include <string>
#include <map>

using namespace std;

void routes(crow::SimpleApp &app, DBEngine &DB_engine){
    //int DBEngine::create_database(std::string name)
    CROW_ROUTE(app, "/createDB").methods("POST"_method)
        ([&DB_engine](const crow::request& req){

            
            json parsed = json::parse(req.body);
            string name = parsed.at("name").dump();
            return std::to_string(DB_engine.create_database(name));
        });

    CROW_ROUTE(app, "/listDBs").methods("GET"_method)
        ([&DB_engine](){

            json j = DB_engine.list_databases();
            std::ostringstream os;
            os << j;
            return os.str();
        });

    
    CROW_ROUTE(app, "/createCollection").methods("GET"_method)
        ([&DB_engine](/*int db_id, string collectionName*/const crow::request& req){
            json parsed = json::parse(req.body);

            int collId = DB_engine.create_collection(stoi(parsed.at("db_id").dump()), parsed.at("collectionName").dump());
            return std::to_string(collId);
        });

    CROW_ROUTE(app, "/listCollection").methods("GET"_method)
        ([&DB_engine](/*int id*/const crow::request& req){
            json parsed = json::parse(req.body);

            json j = DB_engine.list_collections(stoi(parsed.at("db_id").dump()));
            std::ostringstream os;
            os << j;
            return os.str();
            
        });


    CROW_ROUTE(app, "/createDocument").methods("GET"_method)
        ([&DB_engine](/*int db_id, int collection_id*/const crow::request& req){
            json parsed = json::parse(req.body);

            int docId = DB_engine.create_document(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()));

            
            return std::to_string(docId);
        });

    
    CROW_ROUTE(app, "/listDocuments").methods("GET"_method)
        ([&DB_engine](const crow::request& req){

            json parsed = json::parse(req.body);

            json j = DB_engine.list_documents(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()));


            
            std::ostringstream os;
            os << j;
            return crow::response(os.str());                                                //try with and without crow::response
        });


Document& DBEngine::get_document(int database_id, int collection_id, int document_id) {
    CROW_ROUTE(app, "/fetchDocument").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);

            json j = DB_engine.get_document_body(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()), stoi(parsed.at("doc_id").dump()));

            j.dump(0);
            std::ostringstream os;
            os << j;
            return os.str();
        });


//int DBEngine::update_document(int database_id, int collection_id, int document_id, std::string body) {
    CROW_ROUTE(app, "/updateDocument/<int>/<int>/<int>")
        .methods("POST"_method)
        ([&DB_engine](const crow::request& req, int database_id, int collection_id, int document_id){
            auto x = crow::json::load(req.body);
            if (!x)
                return crow::response(400);
            std::ostringstream os;
            os << x;
            return crow::response(DB_engine.update_document(database_id, collection_id, document_id, os.str()));
        });
}



int main()
{
    crow::SimpleApp app;
    crow::mustache::set_base(".");

    DBEngine DB_engine("../../../data");

    CROW_ROUTE(app, "/")
    ([] {
        crow::mustache::context ctx;
        return crow::mustache::load("jsonfield.html").render();
    });

    routes(app, DB_engine);


    app.port(4000)
    .multithreaded()
    .run();
}

