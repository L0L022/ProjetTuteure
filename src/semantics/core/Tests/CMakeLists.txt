FILE(GLOB HEADERS ${INCLUDE_DIR}/semantics/core/Tests/*.hpp)

add_executable(semantics_core_data_tests DataTests.cpp ${HEADERS})
target_include_directories(semantics_core_data_tests SYSTEM PUBLIC ${INCLUDE_DIR})
target_link_libraries(semantics_core_data_tests lib_core)
target_link_libraries(semantics_core_data_tests Qt5::Test)
add_test(NAME semantics_core_data_tests COMMAND semantics_core_data_tests)
