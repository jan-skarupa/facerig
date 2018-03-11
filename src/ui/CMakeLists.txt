find_package(Qt5Widgets)

file(GLOB SOURCE_FILES *.cpp *.h)
get_filename_component(MAIN main.cpp ABSOLUTE)
list(REMOVE_ITEM SOURCE_FILES ${MAIN})

qt5_wrap_ui(UI_HEADERS mainwindow.ui)

add_library(UI ${SOURCE_FILES} ${UI_HEADERS})
target_link_libraries(UI Qt5::Widgets)
