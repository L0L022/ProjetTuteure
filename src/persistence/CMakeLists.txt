set(SRC DAOFactory.cpp Tables.cpp)

add_subdirectory(SQLite)

FILE(GLOB HEADERS ${INCLUDE_DIR}/persistence/*.hpp)

add_library(lib_persistence STATIC ${SRC} ${HEADERS})
target_include_directories(lib_persistence SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_persistence Qt5::Core)

add_executable(lib_persistence_tests Tests.cpp ${HEADERS})
target_link_libraries(lib_persistence_tests lib_persistence)
target_link_libraries(lib_persistence_tests Qt5::Test)
add_test(NAME lib_persistence_tests COMMAND lib_persistence_tests)
