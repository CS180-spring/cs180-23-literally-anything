#include "crow.h"
#include "../db/db_engine.h"

#include "../../../include/nlohmann/json.hpp"
using json = nlohmann::json;

#include <sstream>
#include <string>
#include <map>

using namespace std;


int main()
{
    crow::SimpleApp app;
    crow::mustache::set_base(".");

    DBEngine DB_engine("../data");

    CROW_ROUTE(app, "/")
    ([] {
        crow::mustache::context ctx;
        return crow::mustache::load("jsonfield.html").render();
    });

    CROW_ROUTE(app, "/createDB/<string>")
        ([](const crow::request& req, string name){
            return DB_engine.create_database(name);
        });

    CROW_ROUTE(app, "/listDB")
        ([](const crow::request& req, string name){
            json j = DB_engine.list_databases();
            std::ostringstream os;
            os << j;
            return os.str();
        });
    
    CROW_ROUTE(app, "/createCollection/<string>/<string>")
        ([](const crow::request& req, string dbName, string collectionName){
            return DB_engine.create_collection(dbName, collectionName);
        });

    CROW_ROUTE(app, "/listCollection/<int>")
        ([](const crow::request& req, int id){
            json j = DB_engine.list_collections(id);
            std::ostringstream os;
            os << j;
            return os.str();
        });

    CROW_ROUTE(app, "/createDocument/<int>/<int>")
        ([](const crow::request& req, int db_id, int collection_id){
            return DB_engine.create_document(db_id, collection_id);
        });

    CROW_ROUTE(app, "/listDocuments/<int>/<int>")
        ([](const crow::request& req, int db_id, int collection_id){
            json j = DB_engine.list_documents(db_id, collection_id);
            std::ostringstream os;
            os << j;
            return os.str();
        });

    CROW_ROUTE(app, "/fetchDocument/<int>/<int>/<int>")
        ([](const crow::request& req, int database_id, int collection_id, int document_id){
            json j = DB_engine.get_document(database_id, collection_id, document_id);
            std::ostringstream os;
            os << j;
            return os.str();
        });

//    int update_document(int database_id, int collection_id, int document_id, std::string body);

        CROW_ROUTE(app, "/updateDoctument/<int>/<int>/<int>/")
        .methods("POST"_method)
        ([](const crow::request& req, int database_id, int collection_id, int document_id){
            auto x = crow::json::load(req.body);
            if (!x)
                return crow::response(400);
            std::ostringstream os;
            os << x;
            return DB_engine.update_document(database_id, collection_id, document_id, os.str())
        });


    app.port(4000)
    .multithreaded()
    .run();
}