#include <catch_amalgamated.hpp>
#include <../src/backend/api/api.h>
#include <json.hpp>
#include <typeinfo>
#include <string>
using namespace std;
using namespace crow;
using json = nlohmann::json;
int dbid,collid,docid;
TEST_CASE("Create DB,Collection,Document")
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
        CHECK(res.code==200);
        CHECK(typeid(res.body).name()=="i");
        dbid=stoi(res.body);

        jj["collectionName"]="test456";
        jj["db_id"]=dbid;
        req.body = jj.dump();
        req.url = "/createCollection";
        req.method=HTTPMethod::GET;
        app.handle(req,res);
        CHECK(res.code==200);
        CHECK(typeid(res.body).name()=="i");
        collid = stoi(res.body);

        jjj["db_id"]=dbid;
        jjj["coll_id"] = collid;
        req.body=jjj.dump();
        req.url="/createDocument";
        req.method=HTTPMethod::GET;
        app.handle(req,res);
        CHECK(res.code==200);
        CHECK(typeid(res.body).name()=="i");
        docid=stoi(res.body);
    }
}
TEST_CASE("List"){
    SimpleApp app;
    mustache::set_base(".");
    DBEngine DB_engine("../data");
    API api;
    api.setup_routes(app, DB_engine);
    app.validate();
    SECTION("List Databases"){
        request req;
        response res;

    }
    SECTION("List Collections"){
        request req;
        response res;
    }
    SECTION("List Documents"){
        request req;
        response res;
    }
}