set(SRC MainWindow.cpp)
SET(RESOURCES ui/ui.qrc)

FILE(GLOB HEADERS ${INCLUDE_DIR}/presentation/*.hpp)

add_library(lib_presentation STATIC ${SRC} ${HEADERS} ${RESOURCES})
target_include_directories(lib_presentation SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_presentation lib_core)
target_link_libraries(lib_presentation Qt5::WebEngineWidgets)
