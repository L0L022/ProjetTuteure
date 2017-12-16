add_subdirectory(semantics)
#add_subdirectory(presentation)
add_subdirectory(persistence)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core WebChannel WebSockets WebEngineWidgets)


add_executable(app main.cpp ${GUI_DIR}/gui.qrc)
target_link_libraries(app lib_core)
