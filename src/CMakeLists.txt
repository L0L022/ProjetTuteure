if (BUILD_PERSISTENCE)
    add_subdirectory(persistence)
endif()

if (BUILD_SEMANTICS)
    add_subdirectory(semantics)
endif()

if (BUILD_PRESENTATION)
    add_subdirectory(presentation)
endif()

if (BUILD_APP)
    add_executable(app main.cpp)
    target_link_libraries(app lib_presentation)
endif()
