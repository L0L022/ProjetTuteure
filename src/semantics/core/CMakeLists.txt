set(SRC Server.cpp Services.cpp WebSocketTransport.cpp WebSocketClientWrapper.cpp)

FILE(GLOB HEADERS ${INCLUDE_DIR}/semantics/core/*.hpp)

add_library(lib_core STATIC ${SRC} ${HEADERS})
target_include_directories(lib_core SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_core Qt5::Core Qt5::WebChannel Qt5::WebSockets)
