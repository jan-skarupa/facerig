#include "render_facade.h"


RenderFacade::RenderFacade(ContextType type, WindowSize window_size)
{
    if (type == ContextType::qlfw) {
        window = create_glfw_context_window(window_size);
        glEnable(GL_DEPTH_TEST);
        render = Render::make_default_render();
    } else {
        std::cout << "Qt context type not implemented." << std::endl;
        throw;
    }
}

RenderFacade::~RenderFacade()
{
    glfwTerminate();
}


void RenderFacade::set_puppet(std::string object_path)
{
    puppet_id = render->add_model(object_path);
}

/*
void RenderFacade::set_puppet_pose(Features features)
{
    glm::mat4 matrix;
    float factor = features.head.rotation.horizontal;
    matrix = glm::rotate(matrix, factor, glm::vec3(0.0f, 1.0f, 0.0f));

    matrix = glm::scale(matrix, glm::vec3(0.1f, 0.1f, 0.1f));
    // render->set_object_transformation(puppet_id, "Cube_Cube.001", matrix);
}
 */

void RenderFacade::render_scene()
{
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Features features;
    // features.head.rotation.horizontal = 1.2;
    // set_puppet_pose(features);

    render->render_scene();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void RenderFacade::run_glfw_render()
{
    render->init_scene();

    while(!glfwWindowShouldClose(window))
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        render_scene();
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* RenderFacade::create_glfw_context_window(const WindowSize& window_size)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(window_size.width, window_size.height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw;
    }

    glViewport(0, 0, window_size.width, window_size.height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}