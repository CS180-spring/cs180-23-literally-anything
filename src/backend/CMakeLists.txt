add_executable(start_api start_server.cpp)

add_subdirectory(db)
add_subdirectory(api)

target_link_libraries(ApiModule PUBLIC DatabaseModule)

target_link_libraries(start_api
    PRIVATE
        ApiModule
)

target_link_libraries(db_engine_test
    PRIVATE
        DatabaseModule
)

# target_link_libraries(api_test
#     PRIVATE
#         ApiModule
# )