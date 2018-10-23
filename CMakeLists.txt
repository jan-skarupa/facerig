cmake_minimum_required(VERSION 3.5)
project(FaceRig)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src/input_pipeline)
add_subdirectory(src/render)

add_executable(FaceRig src/main.cpp)
target_link_libraries(FaceRig InputPipeline Render)
