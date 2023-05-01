ADD_LIBRARY(DatabaseModule "")

target_sources(DatabaseModule
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/document.cpp
        ${CMAKE_CURRENT_LIST_DIR}/collection.cpp
        ${CMAKE_CURRENT_LIST_DIR}/database.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/db_engine.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/document.h
        ${CMAKE_CURRENT_LIST_DIR}/collection.h
        ${CMAKE_CURRENT_LIST_DIR}/database.h 
        ${CMAKE_CURRENT_LIST_DIR}/db_engine.h 
)

target_include_directories(DatabaseModule
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

target_link_libraries(DatabaseModule PUBLIC nlohmann_json::nlohmann_json) 