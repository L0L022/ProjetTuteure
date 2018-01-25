set(SRC DAO.cpp DAOFactory.cpp Exceptions.cpp)
set(RESSOURCES sqlite.qrc)

FILE(GLOB HEADERS ${INCLUDE_DIR}/persistence/SQLite/*.hpp)

add_library(lib_persistence_sqlite STATIC ${SRC} ${HEADERS} ${RESSOURCES})
target_include_directories(lib_persistence_sqlite SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_persistence_sqlite Qt5::Core Qt5::Sql)
target_link_libraries(lib_persistence_sqlite lib_persistence)
