cmake_minimum_required(VERSION 3.5)
project(FaceRig)

set(CMAKE_PREFIX_PATH /home/head/Qt/5.10.0/gcc_64)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src/render)

add_executable(RenderTest src/render/main.cpp)
target_link_libraries(RenderTest Render)
set_target_properties(RenderTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(src/camera)

add_executable(CameraTest src/camera/main.cpp)
target_link_libraries(CameraTest Camera)
set_target_properties(CameraTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(src/ui)

add_executable(FaceRig src/main.cpp)
target_link_libraries(FaceRig UI Camera)
set_target_properties(FaceRig PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
