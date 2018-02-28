cmake_minimum_required(VERSION 3.5)
project(FaceRig)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(OPENGL_LIB -lglfw3 -lXrandr -lX11 -lXxf86vm -lpthread -lXcursor -lXinerama -ldl)
set(RENDER_LIB lib/glad.c)
set(RENDER_SRC src/render/main.cpp src/render/render.cpp src/render/render.h)

add_executable(Render ${RENDER_SRC} ${RENDER_LIB})
target_link_libraries(Render ${OPENGL_LIB})
set_target_properties(Render PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")