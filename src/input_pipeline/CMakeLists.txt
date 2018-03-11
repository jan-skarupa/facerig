find_package(OpenCV REQUIRED)

file(GLOB SOURCE_FILES *.cpp *.h analyzers/*.cpp analyzers/*.h)
get_filename_component(MAIN main.cpp ABSOLUTE)
list(REMOVE_ITEM SOURCE_FILES ${MAIN})

add_library(InputPipeline ${SOURCE_FILES})
target_link_libraries(InputPipeline ${OpenCV_LIBS} dlib::dlib)
