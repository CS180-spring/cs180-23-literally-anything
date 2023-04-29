#ifndef API_H
#define API_H

#include "../db/db_engine.h"
//#include "crow.h"
#include "../../../include/crowcpp/crow_all.h"

#include <sstream>
#include <string>
#include <unordered_map>


class API {
   public:
    //API();
    static void setup_routes(crow::SimpleApp &app, DBEngine &DB_engine);
};

#endif