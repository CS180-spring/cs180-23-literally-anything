#include <gtest/gtest.h>
#include "api.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <string>
#include <cctype>
using json = nlohmann::json;
int dbid = 0;
int collid = 0;
int docid = 0;
//if it gives handle_full error add this to your crow app.h header
// void handle_full(request& req, response& res)
//         {
//             auto found = handle_initial(req, res);
//             if (found->rule_index)
//                 handle(req, res, found);
//         }
TEST(CreateTest, ApiTests)
{
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    
    nlohmann::json j;
    nlohmann::json jj;
    nlohmann::json jjj;
    j["name"] = "test123";
    crow::request req;
    crow::response res;
    req.url = "/createDB";
    req.body = j.dump();
    cout << j.dump() << endl;
    req.method = crow::HTTPMethod::POST;
    app.handle_full(req, res);
    std::cout <<"aaa" <<res.body <<"aaa"<< endl;
    //EXPECT_EQ(res.code, 200);
    int db = std::stoi(res.body);
    dbid=db;

    jj["collectionName"] = "test456";
    jj["db_id"] = dbid;
    req.body = jj.dump();
    req.url = "/createCollection";
    req.method = crow::HTTPMethod::GET;
    app.handle_full(req, res);
    //EXPECT_EQ(res.code, 200);
    collid = std::stoi(res.body);

    jjj["db_id"] = dbid;
    jjj["coll_id"] = collid;
    req.body = jjj.dump();
    req.url = "/createDocument";
    req.method = crow::HTTPMethod::GET;
    app.handle_full(req, res);
    //EXPECT_EQ(res.code, 200);
    docid = std::stoi(res.body);
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
    std::cout << res.body << endl;
    EXPECT_EQ(res.code, 200);

    req.url = "/listCollection";
    req.url_params=crow::query_string("/listCollection?db_id="+to_string(dbid)); 
    req.method = crow::HTTPMethod::GET;
    app.handle_full(req, res);
    std::cout << res.body << endl;
    EXPECT_EQ(res.code, 200);

    nlohmann::json jjj;
    jjj["db_id"] = dbid;
    jjj["coll_id"] = collid;
    req.url = "/listDocuments";
    req.method = crow::HTTPMethod::GET;
    req.body = jjj.dump();
    app.handle_full(req, res);
    std::cout << res.body << endl;
    EXPECT_EQ(res.code, 200);
}
TEST(CollectionCount, ApiTests){
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    crow::request req;
    crow::response res;
    req.url = "/collectionCount";
    req.method = crow::HTTPMethod::GET;
    req.url_params = crow::query_string("/collectionCount?db_id="+to_string(dbid));
    app.handle_full(req,res);
    EXPECT_EQ(res.code,200);
    EXPECT_EQ(res.body,"1");
}
TEST(DocumentCount, ApiTests){
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    crow::request req;
    crow::response res;
    req.url = "/docCount";
    req.method = crow::HTTPMethod::GET;
    req.url_params = crow::query_string("/docCount?db_id="+to_string(dbid)+"&coll_id="+to_string(collid));
    app.handle_full(req,res);
    EXPECT_EQ(res.code,200);
    EXPECT_EQ(res.body,"1");
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
    testjson["s"] = "teststring";
    testjson["i"] = 1234;
    testjson["b"] = true;
    cout << testjson.dump() << endl;
    testurl = "/updateDocument/" + to_string(dbid) + "/" + to_string(collid) + "/" + to_string(docid);
    std::cout << testurl << endl;
    req.method = crow::HTTPMethod::POST;
    req.url = testurl;
    req.body = testjson.dump();
    app.handle_full(req, res);
    EXPECT_EQ(res.code, 200);
    EXPECT_EQ(res.body, "0");
}
TEST(FetchDocument, ApiTests)
{
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    crow::request req;
    crow::response res;
    nlohmann::json jtest;
    jtest["db_id"] = dbid;
    jtest["coll_id"] = collid;
    jtest["doc_id"] = docid;
    req.body = jtest.dump();
    req.url = "/fetchDocument";
    req.method = crow::HTTPMethod::GET;
    app.handle_full(req, res);
    EXPECT_EQ(res.code, 200);
    auto result = nlohmann::json::parse(res.body);
    string teststring = result.dump();
    std::cout << res.body << endl;
    std::cout << teststring << endl;
    EXPECT_EQ(res.body, "{\"b\":true,\"i\":1234,\"s\":\"teststring\"}");
}
TEST(SearchTest, ApiTests)
{
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    crow::request req;
    crow::response res;
    json j;
    j["db_id"] = dbid;
    j["coll_id"]=collid;
    j["query_key"]="s";
    j["query_val"] ="teststring";
    req.body=j.dump();
    req.url="/searchContent";
    req.method=crow::HTTPMethod::GET;
    app.handle_full(req,res);
    EXPECT_EQ(res.code,200);
    EXPECT_EQ(res.body,"{\"b\":true,\"i\":1234,\"s\":\"teststring\"}");
}
 TEST(DeleteDocument, ApiTests){
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    crow::request req;
    crow::response res;
    nlohmann::json j;
    j["db_id"]=dbid;
    j["coll_id"]=collid;
    j["doc_id"]=docid;
    cout<<dbid<<endl<<collid<<endl<<docid<<endl;
    req.url="/deleteDoc";
    req.method=crow::HTTPMethod::GET;
    req.body=j.dump();
    std::cout<<req.body<<endl;
    app.handle_full(req,res);
    EXPECT_EQ(res.code,200);
    EXPECT_EQ(res.body,"0");
 }
 TEST(DeleteCollection, ApiTests){
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    crow::request req;
    crow::response res;
    json j;
    j["db_id"]=dbid;
    j["coll_id"]=collid;
    req.url="/deleteColl";
    req.method=crow::HTTPMethod::GET;
    req.body=j.dump();
    app.handle_full(req,res);
    EXPECT_EQ(res.code,200);
    EXPECT_EQ(res.body,"0");
 }
 TEST(DeleteDatabase, ApiTests){
    crow::App<crow::CORSHandler> app;
    auto &cors = app.get_middleware<crow::CORSHandler>();
    DBEngine DB_engine("../../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    crow::request req;
    crow::response res;
    json j;
    j["db_id"]=dbid;
    req.url="/deleteDB";
    req.method=crow::HTTPMethod::GET;
    req.body=j.dump();
    app.handle_full(req,res);
    EXPECT_EQ(res.code,200);
    EXPECT_EQ(res.body,"0");
 }
