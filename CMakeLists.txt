cmake_minimum_required(VERSION 3.0)

project(ProjetTuteure)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core WebChannel WebSockets WebEngineWidgets)
find_package(Qt5 COMPONENTS Sql)
find_package(Qt5 COMPONENTS Test)

enable_testing()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)
