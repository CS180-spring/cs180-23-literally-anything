#include <gtest/gtest.h>
#include "api.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <string>
static char buf[2048];
TEST(CreateTest, AdvTests){
    crow::App<crow::CORSHandler> app;
    auto& cors = app.get_middleware<crow::CORSHandler>();
    auto _ = async(launch::async,[&] {app.bindaddr("127.0.0.1").port(45451).run(); });
    app.wait_for_server_start();
    std::string sendmsg = "POST /createDB \r\nContent-Length:3\r\nX-HeaderTest: 123\r\n\r\nA=B\r\n";
    boost::asio::io_service is;
    {
        boost::asio::ip::tcp::socket c(is);
        c.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"),45451));
        c.send(boost::asio::buffer(sendmsg));
        size_t recved = c.receive(boost::asio::buffer(buf,2048));
        EXPECT_EQ(buf[recved-1]);
    }
    app.stop();
}