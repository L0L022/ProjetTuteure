set(SRC MainWindow.cpp)
set(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist/ui.qrc)

message(STATUS "presentation ui: npm install")
execute_process(COMMAND cmd /c npm install
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui)

message(STATUS "presentation ui: npm run build")
execute_process(COMMAND cmd /c npm run build
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui)

message(STATUS "presentation ui: generate ui.qrc")
message(STATUS "${Qt5Core_RCC_EXECUTABLE}")
execute_process(COMMAND ${Qt5Core_RCC_EXECUTABLE})
execute_process(COMMAND cmd /c ${Qt5Core_RCC_EXECUTABLE} -o ui.qrc -project
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist)

FILE(GLOB HEADERS ${INCLUDE_DIR}/presentation/*.hpp)

add_library(lib_presentation STATIC ${SRC} ${HEADERS} ${RESOURCES})
target_include_directories(lib_presentation SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_presentation lib_core)
target_link_libraries(lib_presentation Qt5::WebEngineWidgets)
