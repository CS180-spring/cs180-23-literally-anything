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
set(JSON_Install ON CACHE INTERNAL "")

set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(json
  # GIT_REPOSITORY https://github.com/nlohmann/json.git
  # GIT_TAG master
  URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
  )

FetchContent_MakeAvailable(json)

message(STATUS "asio...")
FetchContent_Declare(asio
  # GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  # GIT_TAG master
  URL https://sourceforge.net/projects/asio/files/asio/1.28.0%20%28Stable%29/asio-1.28.0.tar.gz/download
  )

FetchContent_MakeAvailable(asio)
add_library(asio INTERFACE)
set(ASIO_INCLUDE_DIR "${asio_SOURCE_DIR}/include")
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/include)
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
  # GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  # GIT_TAG master
  # URL https://github.com/CrowCpp/Crow/tarball/master
  URL https://github.com/CrowCpp/Crow/archive/5f49f9add828fdc6eb0f6192df574522b6713ffb.tar.gz
)
set(CROW_FEATURES ssl)

message(STATUS "json_schema...")

FetchContent_Declare(json_schema
  GIT_REPOSITORY https://github.com/pboettch/json-schema-validator.git
  GIT_TAG 2.2.0
)

FetchContent_MakeAvailable(crow)
FetchContent_MakeAvailable(json_schema)

add_subdirectory(tests)
add_subdirectory(src/backend)

