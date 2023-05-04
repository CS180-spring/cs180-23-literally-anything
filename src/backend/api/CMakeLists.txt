ADD_LIBRARY(ApiModule "")

target_sources(ApiModule
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/api.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/api.h
)

target_include_directories(ApiModule
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(ApiModule PUBLIC asio Crow::Crow nlohmann_json::nlohmann_json) 