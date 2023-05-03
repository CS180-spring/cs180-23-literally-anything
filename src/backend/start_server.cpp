#include "api/api.h"

#include "../../include/nlohmann/json.hpp"
using json = nlohmann::json;

int main()
{
    crow::SimpleApp app;
    crow::mustache::set_base(".");

    DBEngine DB_engine("../../data");

    API api;

    api.setup_routes(app, DB_engine);

    app.port(4000)
    .multithreaded()
    .run();
}