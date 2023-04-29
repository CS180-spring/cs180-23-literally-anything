#include "api.h"

//#include "../include/crowcpp/crow_all.h"

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

    req.url = "/listDBs";

    app.handle(req, res); //res will contain a code of 200, and a response body of "hi"
    
    std::cout << "List DBs endpoint body: " << std::endl;
    std::cout << res.body << std::endl;
    std::cout << "returned code: ";
    std::cout << res.code << std::endl;

    req.url = "/listCollection";

    app.handle(req, res); //res will contain a code of 200, and a response body of "hi"
    
    std::cout << "List collection endpoint body: " << std::endl;
    std::cout << res.body << std::endl;
    std::cout << "returned code: ";
    std::cout << res.code << std::endl;

}
    