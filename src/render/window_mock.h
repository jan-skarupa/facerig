#ifndef FACERIG_WINDOW_MOCK_H
#define FACERIG_WINDOW_MOCK_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

GLFWwindow* create_context_window(int width, int height);
void        framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif // FACERIG_WINDOW_MOCK_H
