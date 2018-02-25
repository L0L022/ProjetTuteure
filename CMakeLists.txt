cmake_minimum_required(VERSION 3.1)

project(ProjetTuteure)

set(BUILD_APP TRUE CACHE BOOL "Build the all application.")
set(BUILD_PRESENTATION TRUE CACHE BOOL "Build presentation.")
set(BUILD_PERSISTENCE TRUE CACHE BOOL "Build persistence.")
set(BUILD_PERSISTENCE_SQLITE TRUE CACHE BOOL "Build persistence sqlite.")
set(BUILD_SEMANTICS TRUE CACHE BOOL "Build semantics.")
set(BUILD_TESTS TRUE CACHE BOOL "Build tests.")

set(CMAKE_CXX_STANDARD 14)
set(QT_MINIMUM_VERSION 5.10.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if (BUILD_APP AND NOT(BUILD_PRESENTATION AND BUILD_PERSISTENCE AND BUILD_SEMANTICS))
    message(FATAL_ERROR "You have de build them all.")
endif()

if (BUILD_PRESENTATION)
    find_package(Qt5 ${QT_MINIMUM_VERSION} COMPONENTS Core WebChannel WebSockets WebEngineWidgets REQUIRED)
endif()

if (BUILD_SEMANTICS)
    find_package(Boost 1.65 REQUIRED)
    include_directories(${Boost_INCLUDE_DIR})
endif()

if (BUILD_PERSISTENCE_SQLITE)
    if (NOT BUILD_PERSISTENCE)
        message(FATAL_ERROR "You have to build persistence in order to build persistence_sqlite.")
    endif()
    find_package(Qt5 ${QT_MINIMUM_VERSION} COMPONENTS Sql REQUIRED)
endif()

if (BUILD_TESTS)
    find_package(Qt5 ${QT_MINIMUM_VERSION} COMPONENTS Test REQUIRED)
    enable_testing()
endif()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(src)
