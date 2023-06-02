#include "api.h"

#include "../../../include/nlohmann/json.hpp"
using json = nlohmann::json;

int main()
{
    crow::SimpleApp app;
    crow::mustache::set_base(".");

    DBEngine DB_engine("../../../data");

    API api;

    api.setup_routes(app, DB_engine);
    
    app.validate();

    crow::request req;
    crow::response res;


    req.url = "/createDB";
    req.body = "{ \"name\": \"API TEST\"}";
    json j;
    j["name"] = "API TEST";
    req.body = j.dump();
    req.method = crow::HTTPMethod::POST;
    app.handle(req, res);

    std::cout << "Created DB ID: " << res.body << std::endl;

    req.url = "/listDBs";
    req.method = crow::HTTPMethod::GET;

    req.body = "";

    app.handle(req, res);
    
    std::cout << "List DBs endpoint body: " << std::endl;
    std::cout << res.body << std::endl;
    std::cout << "returned code: ";
    std::cout << res.code << std::endl;

    req.url = "/listCollection";

    app.handle(req, res);
    
    std::cout << "List collection endpoint body: " << std::endl;
    std::cout << res.body << std::endl;
    std::cout << "returned code: ";
    std::cout << res.code << std::endl;

}
    