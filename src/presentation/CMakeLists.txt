set(SRC MainWindow.cpp)
set(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist/ui.qrc)

message(STATUS "presentation ui: npm install")
execute_process(COMMAND npm install
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui
                OUTPUT_QUIET)

message(STATUS "presentation ui: npm run build")
execute_process(COMMAND npm run build
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui
                OUTPUT_QUIET)

message(STATUS "presentation ui: generate ui.qrc")
execute_process(COMMAND rcc -o ui.qrc -project
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist
                OUTPUT_QUIET)

FILE(GLOB HEADERS ${INCLUDE_DIR}/presentation/*.hpp)

add_library(lib_presentation STATIC ${SRC} ${HEADERS} ${RESOURCES})
target_include_directories(lib_presentation SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_presentation lib_core)
target_link_libraries(lib_presentation Qt5::WebEngineWidgets)
