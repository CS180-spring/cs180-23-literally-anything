#include "../../../include/nlohmann/json.hpp"
#include "../db/db_engine.h"
#include "crow.h"
using json = nlohmann::json;

#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    crow::SimpleApp app;
    crow::mustache::set_base(".");

    DBEngine DB_engine("../../../data");

    CROW_ROUTE(app, "/")
    ([] {
        crow::mustache::context ctx;
        return crow::mustache::load("jsonfield.html").render();
    });

    CROW_ROUTE(app, "/createDB/<string>")
    ([&DB_engine](string dbname) {
        int id = DB_engine.create_database(dbname);
        // int a = DB_engine.create_database(dbname);

        // return DB_engine.create_database(dbname);
        // return -1;
        return std::to_string(id);
        // return 200;
    });

    CROW_ROUTE(app, "/listDBs/<string>")
    ([&DB_engine](string name) {
        json j = DB_engine.list_databases();
        std::ostringstream os;
        os << j;
        return crow::response(os.str());
        // return os.str();
    });

    CROW_ROUTE(app, "/createCollection/<int>/<string>")
    ([&DB_engine](int db_id, string collectionName) {
        int collId = DB_engine.create_collection(db_id, collectionName);
        return std::to_string(collId);
    });

    CROW_ROUTE(app, "/listCollection/<int>")
    ([&DB_engine](int id) {
        json j = DB_engine.list_collections(id);
        std::ostringstream os;
        os << j;
        return crow::response(os.str());
    });

    CROW_ROUTE(app, "/createDocument/<int>/<int>")
    ([&DB_engine](const crow::request& req, int db_id, int collection_id) {
        int docId = DB_engine.create_document(db_id, collection_id);
        return std::to_string(docId);
    });

    CROW_ROUTE(app, "/listDocuments/<int>/<int>")
    ([&DB_engine](const crow::request& req, int db_id, int collection_id) {
        json j = DB_engine.list_documents(db_id, collection_id);
        std::ostringstream os;
        os << j;
        return crow::response(os.str());  // try with and without crow::response
    });

    // Document& DBEngine::get_document(int database_id, int collection_id, int document_id) {
    CROW_ROUTE(app, "/fetchDocument/<int>/<int>/<int>")
    ([&DB_engine](const crow::request& req, int database_id, int collection_id, int document_id) {
        // json j = DB_engine.get_document(database_id, collection_id, document_id).get_content();
        // std::ostringstream os;
        // os << j;
        // return os.str();
        return DB_engine.get_document(database_id, collection_id, document_id).get_content();
    });

    // int DBEngine::update_document(int database_id, int collection_id, int document_id, std::string body) {
    CROW_ROUTE(app, "/updateDoctument/<int>/<int>/<int>/")
        .methods("POST"_method)([&DB_engine](const crow::request& req, int database_id, int collection_id, int document_id) {
            auto x = crow::json::load(req.body);
            if (!x)
                return crow::response(400);
            std::ostringstream os;
            os << x;
            return crow::response(DB_engine.update_document(database_id, collection_id, document_id, os.str()));
        });

    app.port(4000)
        .multithreaded()
        .run();
}