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

    CROW_ROUTE(app, "/listDBs").methods("GET"_method)
        ([&DB_engine](){

            json j = DB_engine.list_databases();
            std::ostringstream os;
            os << j;
            return os.str();
        });


    app.validate();

    crow::request req;
    crow::response res;

    req.url = "/listDBs";

    app.handle(req, res); 
    
    std::cout << res.code;

}
    