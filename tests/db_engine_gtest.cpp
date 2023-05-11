#include <string>
#include <gtest/gtest.h>
#include "db_engine.h"
//using namespace std;
using json = nlohmann::json;

class DBEngineTest : public ::testing::Test {
    protected:
    void SetUp() override {
        DBEngine engine("../../tests/gtest_data");
        int dbid1 = engine.create_database("Database 1");
        int dbid2 = engine.create_database("Database 2");
        int dbid3 = engine.create_database("Database 3");
    }
    
}; 