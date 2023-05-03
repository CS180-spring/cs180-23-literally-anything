cmake_minimum_required(VERSION 3.13)

project(restdb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

message(STATUS "nlohmann/json...")
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG master
  )

FetchContent_MakeAvailable(json)

message(STATUS "asio...")
FetchContent_Declare(asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG master
  )

FetchContent_MakeAvailable(asio)
add_library(asio INTERFACE)
set(ASIO_INCLUDE_DIR "${asio_SOURCE_DIR}/asio/include")
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
target_compile_definitions(asio INTERFACE ASIO_STANDALONE)
find_package(Threads)
target_link_libraries(asio INTERFACE Threads::Threads)

if(WIN32)
  macro(get_win_hex outvar)
    string(REGEX MATCH "^([0-9]+)\\.([0-9]+)" ${outvar} ${CMAKE_SYSTEM_VERSION})
    math(EXPR ${outvar} "(${CMAKE_MATCH_1} << 8) + ${CMAKE_MATCH_2}" OUTPUT_FORMAT HEXADECIMAL)
  endmacro()

  get_win_hex(winver)
  message(STATUS "Set _WIN32_WINNT=${winver}")
  target_compile_definitions(asio INTERFACE _WIN32 _WIN32_WINNT=${winver} __USE_W32_SOCKETS)
endif()

message(STATUS "crow...")

FetchContent_Declare(crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG master
)

FetchContent_MakeAvailable(crow)

add_subdirectory(tests)
add_subdirectory(src/backend)

