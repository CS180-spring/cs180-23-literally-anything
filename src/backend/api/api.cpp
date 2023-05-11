#include "api.h"

#include "../../../include/nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

void API::setup_routes(crow::App<crow::CORSHandler> &app, DBEngine &DB_engine){
    CROW_ROUTE(app, "/createDB").methods("POST"_method)
        ([&DB_engine](const crow::request& req){

            //int DBEngine::create_database(std::string name) {
            json parsed = json::parse(req.body);
            string name = parsed.at("name").dump(-1);
            
            string returnObj = name.erase(0, 1);
            returnObj.pop_back();

            return crow::response(200, "text/plain", std::to_string(DB_engine.create_database(returnObj)));
        });


    CROW_ROUTE(app, "/listDBs").methods("GET"_method)
        ([&DB_engine]() {
            std::unordered_map<int, std::string> db_map = DB_engine.list_databases();
            json j;

            for (const auto& pair : db_map) {
                j.push_back({{"id", pair.first}, {"name", pair.second}});
                
            }

            string returnObj = j.dump(-1).erase(0, 1);
            returnObj.pop_back();
            return crow::response(200, "json", returnObj);
        });

    
    CROW_ROUTE(app, "/createCollection").methods("GET"_method)
        ([&DB_engine](/*int db_id, string collectionName*/const crow::request& req){
            json parsed = json::parse(req.body);

            int collId = DB_engine.create_collection(stoi(parsed.at("db_id").dump()), parsed.at("collectionName").dump());
            return crow::response(200, "text/plain", std::to_string(collId));
        });

    CROW_ROUTE(app, "/listCollection").methods("GET"_method)
        ([&DB_engine](/*int id*/const crow::request& req){
            json parsed = json::parse(req.body);

            json j = DB_engine.list_collections(stoi(parsed.at("db_id").dump()));
            std::ostringstream os;
            os << j;
            return crow::response(200, "text/plain", os.str());
        });


    CROW_ROUTE(app, "/createDocument").methods("GET"_method)
        ([&DB_engine](/*int db_id, int collection_id*/const crow::request& req){
            json parsed = json::parse(req.body);

            int docId = DB_engine.create_document(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()));
            //int docId = DB_engine.create_document(db_id, collection_id);
            return crow::response(200, "text/plain", std::to_string(docId));
        });

    
    CROW_ROUTE(app, "/listDocuments").methods("GET"_method)
        ([&DB_engine](const crow::request& req){

            json parsed = json::parse(req.body);

            json j = DB_engine.list_documents(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()));


            //json j = DB_engine.list_documents(db_id, collection_id);
            std::ostringstream os;
            os << j;
            return crow::response(200, "text/plain", os.str());

        });


//Document& DBEngine::get_document(int database_id, int collection_id, int document_id) {
    CROW_ROUTE(app, "/fetchDocument").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);


            int database_id = stoi(parsed.at("db_id").dump());
            int collection_id = stoi(parsed.at("coll_id").dump());
            int document_id = stoi(parsed.at("doc_id").dump());
            string returnObj = DB_engine.get_document_body(database_id, collection_id, document_id);
            return crow::response(200, "text/plain", returnObj);
        });
    
    CROW_ROUTE(app, "/deleteDB").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);
            int db_id = stoi(parsed.at("db_id").dump());
            return crow::response(200, "text/plain", to_string(DB_engine.delete_database(db_id)));
        });

    CROW_ROUTE(app, "/deleteColl").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);
            int db_id = stoi(parsed.at("db_id").dump());
            int coll_id = stoi(parsed.at("coll_id").dump());
            return crow::response(200, "text/plain", to_string(DB_engine.delete_collection(db_id, coll_id)));
        });

    CROW_ROUTE(app, "/deleteDoc").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);
            int db_id = stoi(parsed.at("db_id").dump());
            int coll_id = stoi(parsed.at("coll_id").dump());
            int doc_id = stoi(parsed.at("doc_id").dump());
            return crow::response(200, "text/plain", to_string(DB_engine.delete_document(db_id, coll_id, doc_id)));
        });

    CROW_ROUTE(app, "/searchContent").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);
        
            
            Collection coll = DB_engine.get_collection(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()));
            //json Collection::search_content_json(std::string field, std::string value)
            auto field = parsed.at("query_key");
            auto key = parsed.at("query_val");
            auto result = coll.search_content_json(field, key);
            string returnObj = result.dump(-1).erase(0, 1);
            returnObj.pop_back();
            return crow::response(200, "json", returnObj);
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
            std::cout << x << endl;
            return crow::response(200, "text/plain", to_string(x));
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



