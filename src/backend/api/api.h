#ifndef API_H
#define API_H

#include "db_engine.h"
#include "crow.h"
//#include "/home/gurmanwsl/cs180-23-literally-anything/include/crowcpp/crow_all.h"
////#include "../../../include/crowcpp/crow_all.h"
#include <crow/middlewares/cors.h>
#include <sstream>
#include <string>
#include <unordered_map>


class API {
   public:
    //API();
    void API::setup_routes(crow::App<crow::CORSHandler> &app, DBEngine &DB_engine);
};

#endif