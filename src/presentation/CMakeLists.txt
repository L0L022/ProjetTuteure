set(SRC MainWindow.cpp)
set(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist/ui.qrc)

message(STATUS "presentation ui: npm install")
if(WIN32)
execute_process(COMMAND cmd /c npm install
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui)
else()
execute_process(COMMAND npm install
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui)
endif()

message(STATUS "presentation ui: npm run build")
if(WIN32)
execute_process(COMMAND cmd /c npm run build
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui)
else()
execute_process(COMMAND npm run build
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui)
endif()

message(STATUS "presentation ui: generate ui.qrc")
if(WIN32)
execute_process(COMMAND cmd /c rcc -o ui.qrc -project
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist)
else()
execute_process(COMMAND ${Qt5Core_RCC_EXECUTABLE} -o ui.qrc -project
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui/dist)
endif()

FILE(GLOB HEADERS ${INCLUDE_DIR}/presentation/*.hpp)

add_library(lib_presentation STATIC ${SRC} ${HEADERS} ${RESOURCES})
target_include_directories(lib_presentation SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(lib_presentation lib_core)
target_link_libraries(lib_presentation Qt5::WebEngineWidgets)
