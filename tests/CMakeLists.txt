add_executable(api_test apitest.cpp)
target_link_libraries(
  api_test
  PRIVATE
  GTest::gtest_main
)
#add_executable(db_engine_gtest db_engine_gtest.cpp)

add_executable(db_engine_test db_engine_test.cpp)