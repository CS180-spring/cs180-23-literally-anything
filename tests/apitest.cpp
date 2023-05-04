#include <gtest/gtest.h>
#include <"../src/backend/api/api.h">
#include <json.hpp>
#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;
using namespace crow;
using json = nlohmann::json;
int dbid,collid,docid;
TEST(CreateTest,ApiTests)
{
    SimpleApp app;
    mustache::set_base(".");
    DBEngine DB_engine("../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();    
    {
        nlohmann::json j;
        nlohmann::json jj;
        nlohmann::json jjj;
        j["name"]="test123";
        request req;
        response res;
        req.url = "/createDB";
        req.body = j.dump();
        req.method = HTTPMethod::POST;
        app.handle(req,res);
        EXPECT_EQ(res.code,200);
        EXPECT_EQ(typeid(res.body).name(),"s");
        std::cout<<res.body<<endl;
        dbid=stoi(res.body);

        jj["collectionName"]="test456";
        jj["db_id"]=dbid;
        req.body = jj.dump();
        req.url = "/createCollection";
        req.method=HTTPMethod::GET;
        app.handle(req,res);
        EXPECT_EQ(res.code,200);
        EXPECT_EQ(typeid(res.body).name(),"s");
        collid = stoi(res.body);

        jjj["db_id"]=dbid;
        jjj["coll_id"] = collid;
        req.body=jjj.dump();
        req.url="/createDocument";
        req.method=HTTPMethod::GET;
        app.handle(req,res);
        EXPECT_EQ(res.code,200);
        EXPECT_EQ(typeid(res.body).name(),"s");
        docid=stoi(res.body);
    }
}
TEST(ListTests,ApiTests){
    SimpleApp app;
    mustache::set_base(".");
    DBEngine DB_engine("../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    request req;
    response res;

    nlohmann::json j;
    req.url = "/listDBs";
    req.method=HTTPMethod::GET;
    app.handle(req,res);
    cout<<res.body<<endl;
    EXPECT_EQ(res.code,200);

    nlohmann::json jj;
    jj["db_id"]=dbid;
    req.url = "/listCollection";
    req.method=HTTPMethod::GET;
    req.body=jj.dump();
    app.handle(req,res);
    cout<<res.body<<endl;
    EXPECT_EQ(res.code,200);

    nlohmann::json jjj;
    jjj["db_id"]=dbid;
    jjj["coll_id"]=collid;
    req.url = "/listDocuments";
    req.method=HTTPMethod::GET;
    req.body=jjj.dump();
    app.handle(req,res);
    cout<<res.body<<endl;
    EXPECT_EQ(res.code,200);

}