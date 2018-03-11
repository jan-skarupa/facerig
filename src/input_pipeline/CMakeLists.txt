find_package(OpenCV REQUIRED)
find_package(Qt5Widgets)

file(GLOB SRC *.cpp *.h analyzers/*.cpp analyzers/*.h mediators/*.cpp mediators/*.h)
get_filename_component(CAMERA_ENTRYPOINT main.cpp ABSOLUTE)
list(REMOVE_ITEM SRC ${CAMERA_ENTRYPOINT})

add_library(Camera ${SRC})
target_link_libraries(Camera Qt5::Widgets ${OpenCV_LIBS})
