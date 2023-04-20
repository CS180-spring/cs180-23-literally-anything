#include "db_engine.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "../../../include/nlohmann/json.hpp"
using json = nlohmann::json;

DBEngine::DBEngine(std::string root_path) {
    // create root directory in the given path root_path/root
    root_path = root_path.append("/root");
    const std::filesystem::path root{root_path};
    std::filesystem::create_directory(root);

    // traverse root_path

    std::string dir_name;
    int dir_id;
    std::string db_info_path;
    json db_info;
    Database db;
    std::map<int, Database>::iterator db_it;
    for (std::filesystem::directory_entry const& dir_entry : std::filesystem::directory_iterator{root}) {
        if (dir_entry.is_directory() == true) {
            dir_name = dir_entry.path().filename();
            dir_id = atoi(dir_name);
            db_info_path = dir_entry.path() / "db.json";
            std::ifstream db_info_file(db_info_path);
            db_info = json::parse(db_info_file);
            databases.insert({Database(db_info["id"].get<int>(), db_info["name"].get<std::string>())});

            // dir_id should == db_info["id"].get<int>()
            db_it = databases.find(dir_id)
            if (db_it == databases.end()) {
                // didnt get added or ma
            } else {
                db = db_it->second;
                db.create_c
            }
        }
    }
}

DBEngine::create_database(std::string name) {
    

}