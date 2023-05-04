#include "api.h"

#include "nlohmann/json.hpp"
using json = nlohmann::json;

int main()
{
    //crow::SimpleApp app;
    crow::App<crow::CORSHandler> app;
    crow::mustache::set_base(".");

    auto& cors = app.get_middleware<crow::CORSHandler>();

    // clang-format off
    cors
      .global()
        .headers("X-Custom-Header", "Access-Control-Allow-Origin")
        .methods("POST"_method, "GET"_method)
      .prefix("/cors")
        .origin("example.com")
      .prefix("/nocors")
        .ignore();
    // clang-format on


    DBEngine DB_engine("../../data");

    API api;

    api.setup_routes(app, DB_engine);

    app.port(4000)
    .multithreaded()
    .run();
}