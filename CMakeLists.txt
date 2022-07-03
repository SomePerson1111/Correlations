cmake_minimum_required(VERSION 3.5)

project(Extractor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(nlohmann_json_DIR D:/soft/libs/json)
find_package(nlohmann_json 3.10.5 REQUIRED)

#add_definitions(-DTEST_ALL)

add_executable(Extractor main.cpp)
target_link_libraries(Extractor PRIVATE nlohmann_json::nlohmann_json)
