cmake_minimum_required(VERSION 3.5)
project(FaceRig)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(OPENGL_LIB -lglfw3 -lXrandr -lX11 -lXxf86vm -lpthread -lXcursor -lXinerama -ldl -lassimp)
set(RENDER_LIB lib/glad.c lib/stb_image.cpp)
file(GLOB RENDER_SRCs src/render/*.cpp src/render/*.h)

add_executable(Render ${RENDER_SRCs} ${RENDER_LIB})
target_link_libraries(Render ${OPENGL_LIB})
set_target_properties(Render PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
