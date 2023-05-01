#include "api.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;


using namespace std;

void API::setup_routes(crow::SimpleApp &app, DBEngine &DB_engine){
    CROW_ROUTE(app, "/createDB").methods("POST"_method)
        ([&DB_engine](const crow::request& req){

            //int DBEngine::create_database(std::string name) {
            json parsed = json::parse(req.body);
            string name = parsed.at("name").get<std::string>();
            return std::to_string(DB_engine.create_database(name));
        });

    CROW_ROUTE(app, "/listDBs").methods("GET"_method)
        ([&DB_engine](){

            json j = DB_engine.list_databases();
            std::ostringstream os;
            os << j;
            return os.str();
            //return os.str();
        });

    
    CROW_ROUTE(app, "/createCollection").methods("GET"_method)
        ([&DB_engine](/*int db_id, string collectionName*/const crow::request& req){
            json parsed = json::parse(req.body);

            int collId = DB_engine.create_collection(stoi(parsed.at("db_id").dump()), parsed.at("collectionName").get<std::string>());
            return std::to_string(collId);
        });

    CROW_ROUTE(app, "/listCollection").methods("GET"_method)
        ([&DB_engine](/*int id*/const crow::request& req){
            json parsed = json::parse(req.body);

            json j = DB_engine.list_collections(stoi(parsed.at("db_id").dump()));
            string jstr = to_string(j);
            // std::ostringstream os;
            // os << j;
            // return os.str();
            return jstr;
            
        });


    CROW_ROUTE(app, "/createDocument").methods("GET"_method)
        ([&DB_engine](/*int db_id, int collection_id*/const crow::request& req){
            json parsed = json::parse(req.body);

            int docId = DB_engine.create_document(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()));

            //int docId = DB_engine.create_document(db_id, collection_id);
            return std::to_string(docId);
        });

    
    CROW_ROUTE(app, "/listDocuments").methods("GET"_method)
        ([&DB_engine](const crow::request& req){

            json parsed = json::parse(req.body);

            json j = DB_engine.list_documents(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()));


            //json j = DB_engine.list_documents(db_id, collection_id);
            std::ostringstream os;
            os << j;
            return crow::response(os.str());                                                //try with and without crow::response
        });


//Document& DBEngine::get_document(int database_id, int collection_id, int document_id) {
    CROW_ROUTE(app, "/fetchDocument").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);

            json j = DB_engine.get_document_body(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()), stoi(parsed.at("doc_id").dump()));
            //json j = DB_engine.get_document(database_id, collection_id, document_id).get_content();
            //std::ostringstream os;
            //os << j;
            //return os.str();
            
            // std::ostringstream os;
            // os << j;
            // return os.str();

            return j.get<std::string>();
        });

    
//int DBEngine::update_document(int database_id, int collection_id, int document_id, std::string body) {
    CROW_ROUTE(app, "/updateDoctument/<int>/<int>/<int>")
        .methods("POST"_method)
        ([&DB_engine](const crow::request& req, int database_id, int collection_id, int document_id){
            json parsed = json::parse(req.body);
            // auto x = crow::json::load(req.body);
            // if (!x)
            //     return crow::response(400);
            // std::ostringstream sos;
            // os << x;
            int x = DB_engine.update_document(database_id, collection_id, document_id, parsed.dump());
            cout << x << endl;
            return crow::response(200, to_string(x));
        });

    CROW_CATCHALL_ROUTE(app)
        ([](crow::response& res) {
            if (res.code == 404)
            {
                res.body = "The URL does not seem to be correct.";
            }
            else if (res.code == 405)
            {
                res.body = "The HTTP method does not seem to be correct.";
            }
            res.end();
        });
}



