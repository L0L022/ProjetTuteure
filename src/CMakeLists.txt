add_subdirectory(semantics)
add_subdirectory(presentation)
add_subdirectory(persistence)

add_executable(app main.cpp)
target_link_libraries(app lib_presentation)
