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
      .global();
    // clang-format on

    app.ssl_file("../../httpscert/host.cert", "../../httpscert/host.key");


    DBEngine DB_engine("../../data");

    API api;

    api.setup_routes(app, DB_engine);

    app.port(4000)
    .multithreaded()
    .run();
}