#include "api.h"

#include "../../../include/nlohmann/json.hpp"
using json = nlohmann::json;

using namespace std;

void API::setup_routes(crow::App<crow::CORSHandler> &app, DBEngine &DB_engine){
    CROW_ROUTE(app, "/createDB").methods("POST"_method)
        ([&DB_engine](const crow::request& req){

            json parsed = json::parse(req.body);
            string name = parsed.at("name").dump(-1);
            
            string returnObj = name.erase(0, 1);
            returnObj.pop_back();
            

            return crow::response(200, "txt", std::to_string(DB_engine.create_database(returnObj)));
        });


    CROW_ROUTE(app, "/listDBs").methods("GET"_method)
        ([&DB_engine]() {
            std::unordered_map<int, std::string> db_map = DB_engine.list_databases();
            json j = json::array();

            for (const auto& pair : db_map) {
                j.push_back({{"id", pair.first}, {"name", pair.second}});
            }

            //string returnObj = j.dump(-1).erase(0, 1);
            //returnObj.pop_back();
            return crow::response(200, "json", j.dump());
        });

    
    CROW_ROUTE(app, "/createCollection").methods("POST"_method)
        ([&DB_engine](/*int db_id, string collectionName*/const crow::request& req){
            json parsed = json::parse(req.body);

            int collId = DB_engine.create_collection(stoi(parsed.at("db_id").dump()), parsed.at("collectionName").get<string>());
            if (collId < 0) {
                return crow::response(400, "txt", to_string(collId));
            }

            return crow::response(200, "txt", std::to_string(collId));
        });

    CROW_ROUTE(app, "/listCollection").methods("GET"_method, "POST"_method)
        ([&DB_engine](const crow::request& req){

            std::ostringstream os;
            os << req.url_params.get("db_id");  
            auto db_id = stoi(os.str());

            std::unordered_map<int, std::string> coll_map;
            int status = DB_engine.list_collections(db_id, coll_map);
            if (status < 0) {
                return crow::response(400, "txt", to_string(status));
            }

            json j = json::array();

            for (const auto& pair : coll_map) {
                j.push_back({{"id", pair.first}, {"name", pair.second}});
            }

            return crow::response(200, "json", j.dump());
        });


    CROW_ROUTE(app, "/createDocument").methods("POST"_method)
        ([&DB_engine](/*int db_id, int collection_id*/const crow::request& req){
            json parsed = json::parse(req.body);

            int docId = DB_engine.create_document(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()));
            if (docId < 0) {
                return crow::response(400, "txt", std::to_string(docId));
            }
            //int docId = DB_engine.create_document(db_id, collection_id);
            return crow::response(200, "txt", std::to_string(docId));
        });

  CROW_ROUTE(app, "/listDocuments").methods("GET"_method)
        ([&DB_engine](const crow::request& req){

            std::ostringstream os;
            os << req.url_params.get("db_id");  
            int db_id = stoi(os.str());

            std::ostringstream os1;
            os1 << req.url_params.get("coll_id");  
            int coll_id = stoi(os1.str());

            std::vector<int> docs;
            int status = DB_engine.list_documents(db_id, coll_id, docs);
            if (status < 0) {
                return crow::response(400, "txt", to_string(status));
            }

            json j = json::array();

            for (int id : docs) {
                j.push_back({{"id", id}});
            }
            return crow::response(200, "json", j.dump());

        }); 

  
 //Document& DBEngine::get_document(int database_id, int collection_id, int document_id) {
    CROW_ROUTE(app, "/fetchDocument").methods("GET"_method)
        ([&DB_engine](const crow::request& req){

            std::ostringstream os;

            os << req.url_params.get("db_id");
            int db_id = stoi(os.str());

            std::ostringstream os2;

            os2 << req.url_params.get("coll_id");
            int coll_id = stoi(os2.str());

            std::ostringstream os3;

            os3 << req.url_params.get("doc_id");
            int doc_id = stoi(os3.str());

            string body;
            int status = DB_engine.get_document_body(db_id, coll_id, doc_id, body);
            if (status < 0) {
                return crow::response(400, "txt", to_string(status));
            }
            // Might error if body is empty
            return crow::response(200, "json", body);
        });


    CROW_ROUTE(app, "/deleteDB").methods("POST"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);
            int db_id = stoi(parsed.at("db_id").dump());
            int status = DB_engine.delete_database(db_id);
            if (status < 0) { 
                return crow::response(400, "txt", to_string(status));
            }
            return crow::response(200, "txt", to_string(status));
        });

    CROW_ROUTE(app, "/deleteColl").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);
            int db_id = stoi(parsed.at("db_id").dump());
            int coll_id = stoi(parsed.at("coll_id").dump());
            int status = DB_engine.delete_collection(db_id, coll_id);
            if (status < 0) {
                return crow::response(400, "txt", to_string(status));
            }
            return crow::response(200, "txt", to_string(status));
        });

    CROW_ROUTE(app, "/deleteDoc").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);
            int db_id = stoi(parsed.at("db_id").dump());
            int coll_id = stoi(parsed.at("coll_id").dump());
            int doc_id = stoi(parsed.at("doc_id").dump());

            int status = DB_engine.delete_document(db_id, coll_id, doc_id);
            if (status < 0) {
                return crow::response(400, "txt", to_string(status));
            }            
            return crow::response(200, "txt", to_string(status));
        });

    CROW_ROUTE(app, "/searchContent").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            json parsed = json::parse(req.body);
        
            int status;
            Collection& coll = DB_engine.get_collection(stoi(parsed.at("db_id").dump()), stoi(parsed.at("coll_id").dump()), status);
            if (status < 0) {
                return crow::response(400);
            }
            //json Collection::search_content_json(std::string field, std::string value)
            auto key = parsed.at("query_key");
            auto val = parsed.at("query_val");
            json j = json::object({ {"key", key}, {"value", val} });

            json result = coll.search_content_json(j);
            string returnObj = result.dump(-1).erase(0, 1);
            returnObj.pop_back();
            return crow::response(200, "json", returnObj);
        });

    //int DBEngine::update_document(int database_id, int collection_id, int document_id, std::string body) {
    CROW_ROUTE(app, "/updateDoctument")
        .methods("POST"_method)
        ([&DB_engine](const crow::request& req){
            //json parsed = json::parse(req.body);

            //std::ostringstream os;

            //os << req.url_params.get("db_id");
            auto db_id = atoi(req.url_params.get("db_id"));
            auto coll_id = atoi(req.url_params.get("coll_id"));
            auto doc_id = atoi(req.url_params.get("doc_id"));
            //int db = stoi(db_id);

            // std::ostringstream os2;

            // os2 << req.url_params.get("coll_id");
            // int coll_id = stoi(os2.str());

            // std::ostringstream os3;

            // os3 << req.url_params.get("doc_id");
            // int doc_id = stoi(os3.str());

            std::ostringstream os4;

            os4 << req.url_params.get("content");

            auto text = os4.str();

            json j;

            j["content"] = text;

            int status = DB_engine.update_document(db_id, coll_id, doc_id, j);
            if (status < 0) {
                return crow::response(400, "txt", to_string(status));
            }
            return crow::response(200, "txt", to_string(status));
        });


//int DBEngine::get_num_collections(int db_id) {
//int DBEngine::get_num_docs(int db_id, int coll_id) {
 
    CROW_ROUTE(app, "/collectionCount").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            std::ostringstream os;
            os << req.url_params.get("db_id");  
            int db_id = stoi(os.str());

            int x = DB_engine.get_num_collections(db_id);

            return crow::response(200, "txt", to_string(x));
        });

    CROW_ROUTE(app, "/docCount").methods("GET"_method)
        ([&DB_engine](const crow::request& req){
            std::ostringstream os;

            os << req.url_params.get("db_id");  
            int db_id = stoi(os.str());

            std::ostringstream os2;

            os2 << req.url_params.get("coll_id");
            int coll_id = stoi(os2.str());

            int x = DB_engine.get_num_docs(db_id, coll_id);

            return crow::response(200, "txt", to_string(x));
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



