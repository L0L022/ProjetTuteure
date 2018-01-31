set(SRC DAOFactory.cpp Tables.cpp)

FILE(GLOB HEADERS ${INCLUDE_DIR}/persistence/*.hpp)

add_library(lib_persistence STATIC ${SRC} ${HEADERS})
target_include_directories(lib_persistence SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_persistence Qt5::Core)

if (BUILD_PERSISTENCE_SQLITE)
    add_subdirectory(SQLite)
endif()
