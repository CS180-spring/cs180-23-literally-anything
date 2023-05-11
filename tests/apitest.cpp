#include <gtest/gtest.h>
#include "api.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;
using json = nlohmann::json;
int dbid = 0;
int collid = 0;
int docid = 0;
TEST(CreateTest, ApiTests)
{
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    {
        nlohmann::json j;
        nlohmann::json jj;
        nlohmann::json jjj;
        j["name"] = "test123";
        crow::request req;
        crow::response res;
        req.url = "/createDB";
        req.body = j.dump();
        req.method = crow::HTTPMethod::POST;
        app.handle_full(req, res);
        EXPECT_EQ(res.code, 200);
        std::cout << res.body << endl;
        dbid = stoi(res.body);

        jj["collectionName"] = "test456";
        jj["db_id"] = dbid;
        req.body = jj.dump();
        req.url = "/createCollection";
        req.method = crow::HTTPMethod::GET;
        app.handle_full(req, res);
        EXPECT_EQ(res.code, 200);
        collid = stoi(res.body);

        jjj["db_id"] = dbid;
        jjj["coll_id"] = collid;
        req.body = jjj.dump();
        req.url = "/createDocument";
        req.method = crow::HTTPMethod::GET;
        app.handle_full(req, res);
        EXPECT_EQ(res.code, 200);
        docid = stoi(res.body);
    }
}
TEST(ListTests, ApiTests)
{
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    crow::request req;
    crow::response res;

    nlohmann::json j;
    req.url = "/listDBs";
    req.method = crow::HTTPMethod::GET;
    app.handle_full(req, res);
    cout << res.body << endl;
    EXPECT_EQ(res.code, 200);

    nlohmann::json jj;
    jj["db_id"] = dbid;
    req.url = "/listCollection";
    req.method = crow::HTTPMethod::GET;
    req.body = jj.dump();
    app.handle_full(req, res);
    cout << res.body << endl;
    EXPECT_EQ(res.code, 200);

    nlohmann::json jjj;
    jjj["db_id"] = dbid;
    jjj["coll_id"] = collid;
    req.url = "/listDocuments";
    req.method = crow::HTTPMethod::GET;
    req.body = jjj.dump();
    app.handle_full(req, res);
    cout << res.body << endl;
    EXPECT_EQ(res.code, 200);
}
TEST(UpdateDocument, ApiTests)
{
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    crow::request req;
    crow::response res;
    string testurl;
    json testjson;
    testjson["string"] = "teststring";
    testjson["int"] = 1234;
    testjson["bool"] = true;
    cout << testjson.dump() << endl;
    testurl = "/updateDoctument/" + to_string(dbid) + "/" + to_string(collid) + "/" + to_string(docid);
    cout << testurl << endl;
    req.method = crow::HTTPMethod::POST;
    req.url = testurl;
    req.body = testjson.dump();
    app.handle_full(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "0");
}
// TEST(FetchDocument,ApiTests){
//     crow::App<crow::CORSHandler> app;
//     auto &cors = app.get_middleware<crow::CORSHandler>();
//     DBEngine DB_engine("../../data");
//     API api;
//     api.setup_routes(app,DB_engine);
//     app.validate();
//     crow::request req;
//     crow::response res;
//     nlohmann::json jtest;
//     jtest["db_id"]=dbid;
//     jtest["coll_id"]=collid;
//     jtest["doc_id"]=docid;
//     req.body = jtest.dump();
//     req.url = "/fetchDocument";
//     req.method = crow::HTTPMethod::GET;
//     app.handle_full(req,res);
//     EXPECT_EQ(res.code,200);
//     nlohmann::json result = nlohmann::json::parse(res.body);
//     string rstring = result.at("string");
//     int rint=result["int"];
//     bool rbool=result["bool"];
//     EXPECT_EQ(rstring,"teststring");
//     EXPECT_EQ(rint,1234);
//     EXPECT_EQ(rbool,true);
// }