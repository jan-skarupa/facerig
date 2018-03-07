find_package(Qt5Widgets)

file(GLOB SRC *.cpp *.h)
get_filename_component(UI_ENTRYPOINT main.cpp ABSOLUTE)
list(REMOVE_ITEM SRC ${UI_ENTRYPOINT})

qt5_wrap_ui(UI_HEADERS mainwindow.ui)

add_library(UI ${SRC} ${UI_HEADERS})
target_link_libraries(UI Qt5::Widgets)
