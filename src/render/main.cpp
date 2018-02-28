#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "render.h"

GLFWwindow* create_context_window(int width, int height);
void        framebuffer_size_callback(GLFWwindow* window, int width, int height);


int main()
{
    std::cout << "Hello, World!" << std::endl;

    int screen_width = 800;
    int screen_height = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = create_context_window(screen_width, screen_height);

    Render dummy(window);
    dummy.run();

    glfwTerminate();

    return 0;
}


GLFWwindow* create_context_window(const int width, const int height) {

    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw;
    }
    glfwMakeContextCurrent(window);

    // Init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw;
    }

    // Init drawing area & register callback function for window resize.
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}