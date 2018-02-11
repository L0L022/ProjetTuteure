#add_custom_target(lib_presentation_ui_npm_install COMMAND npm --prefix ${CMAKE_CURRENT_SOURCE_DIR} install)

#add_custom_target(lib_presentation_ui_npm_build COMMAND npm --prefix ${CMAKE_CURRENT_SOURCE_DIR} run build)
#add_dependencies(lib_presentation_ui_npm_build lib_presentation_ui_npm_install)

#add_custom_target(lib_presentation_ui_qrc COMMAND rcc -root ui -o ui.qrc -project WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)
#add_dependencies(lib_presentation_ui_qrc lib_presentation_ui_npm_build)

#add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/package-lock.json COMMAND npm install WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
#add_custom_target(lib_presentation_ui_npm_build COMMAND npm run build WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ui.qrc COMMAND rcc -root ui -o ${CMAKE_CURRENT_BINARY_DIR}/ui.qrc -project DEPENDS lib_presentation_ui_npm_build WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist)
