set(SRC DAOFactory.cpp Tables.cpp)

add_subdirectory(SQLite)

FILE(GLOB HEADERS ${INCLUDE_DIR}/persistence/*.hpp)

add_library(lib_persistence STATIC ${SRC} ${HEADERS})
target_include_directories(lib_persistence SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_persistence Qt5::Core)

# target_link_libraries(lib_persistence lib_persistence_sqlite)

add_executable(persistence_tests Tests.cpp ${HEADERS})
target_include_directories(persistence_tests SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(persistence_tests lib_persistence)
target_link_libraries(persistence_tests Qt5::Test)
add_test(NAME persistence_tests COMMAND persistence_tests)

target_link_libraries(persistence_tests lib_persistence_sqlite)
