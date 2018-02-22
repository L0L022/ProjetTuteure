set(SRC Data.cpp DataServices.cpp Server.cpp Services.cpp UIServices.cpp WebSocketTransport.cpp WebSocketClientWrapper.cpp)

FILE(GLOB HEADERS ${INCLUDE_DIR}/semantics/core/*.hpp)

add_library(lib_core STATIC ${SRC} ${HEADERS})
target_include_directories(lib_core SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_core Qt5::Core Qt5::WebChannel Qt5::WebSockets)
target_link_libraries(lib_core ${Boost_LIBRARIES})
target_link_libraries(lib_core lib_persistence_sqlite)

if (BUILD_TESTS)
    add_subdirectory(Tests)
endif()
