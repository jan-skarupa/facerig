cmake_minimum_required(VERSION 3.5)
project(FaceRig)

# Download (upadte) dlib source files. Set include directories.
set(DLIB_DIR ${CMAKE_SOURCE_DIR}/3dparty/dlib)

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/3dparty/dlib)
    find_package(Git REQUIRED)
    execute_process(COMMAND ${GIT_EXECUTABLE} init WORKING_DIRECTORY "${DLIB_DIR}")
    execute_process(COMMAND ${GIT_EXECUTABLE} remote add -f origin https://github.com/davisking/dlib WORKING_DIRECTORY "${DLIB_DIR}")
    execute_process(COMMAND ${GIT_EXECUTABLE} config core.sparseCheckout true WORKING_DIRECTORY "${DLIB_DIR}")
    file(WRITE ${DLIB_DIR}/.git/info/sparse-checkout "dlib")
    execute_process(COMMAND git pull origin master WORKING_DIRECTORY "${DLIB_DIR}")
endif()

include_directories(${DLIB_DIR})
add_subdirectory(${DLIB_DIR}/dlib)


set(CMAKE_PREFIX_PATH /home/head/Qt/5.10.0/gcc_64)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)
include_directories(${CMAKE_SOURCE_DIR}/include)


add_subdirectory(src/render)
add_executable(RenderTest src/render/main.cpp)
target_link_libraries(RenderTest Render)
set_target_properties(RenderTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(src/input_pipeline)
set(MEDLOC src/input_pipeline/mediators)
file(GLOB MEDIATORS ${MEDLOC}/pipeline_ui_mediator.h ${MEDLOC}/mock_mediator.h ${MEDLOC}/mock_mediator.cpp)
add_executable(CameraTest src/input_pipeline/main.cpp ${MEDIATORS})
target_link_libraries(CameraTest InputPipeline)
set_target_properties(CameraTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(src/ui)
add_executable(FaceRig src/main.cpp)
target_link_libraries(FaceRig UI InputPipeline)
set_target_properties(FaceRig PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
