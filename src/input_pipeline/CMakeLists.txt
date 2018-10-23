find_package(OpenCV REQUIRED)

file(GLOB SOURCE_FILES *.cpp *.h analyzers/*.cpp analyzers/*.h)

add_library(InputPipeline ${SOURCE_FILES})
target_link_libraries(InputPipeline ${OpenCV_LIBS} dlib -lblas -llapack)
