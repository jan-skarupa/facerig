include_directories(${CMAKE_SOURCE_DIR}/include)

set(OPENGL_LIB -lglfw3 -lXrandr -lX11 -lXxf86vm -lpthread -lXcursor -lXinerama -ldl -lassimp)
set(RENDER_LIB ${CMAKE_SOURCE_DIR}/lib/glad.c ${CMAKE_SOURCE_DIR}/lib/stb_image.cpp)

file(GLOB RENDER_SRC *.cpp *.h)
get_filename_component(RENDER_ENTRYPOINT main.cpp ABSOLUTE)
list(REMOVE_ITEM RENDER_SRC ${RENDER_ENTRYPOINT})

add_library(Render ${RENDER_SRC} ${RENDER_LIB})
target_link_libraries(Render ${OPENGL_LIB})
