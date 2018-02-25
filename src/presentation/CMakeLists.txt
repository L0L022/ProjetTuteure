set(SRC MainWindow.cpp)
set(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist/ui.qrc)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist/index.html
    COMMAND npm install
    COMMAND npm run build
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist/ui.qrc
    COMMAND rm -f ui.qrc
    COMMAND rcc -o ui.qrc -project
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist/index.html
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist)

FILE(GLOB HEADERS ${INCLUDE_DIR}/presentation/*.hpp)

add_library(lib_presentation STATIC ${SRC} ${HEADERS} ${RESOURCES})
target_include_directories(lib_presentation SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_presentation lib_core)
target_link_libraries(lib_presentation Qt5::WebEngineWidgets)
