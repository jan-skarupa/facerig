#ifndef FACERIG_RENDER_H
#define FACERIG_RENDER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Render {
public:
    explicit Render(GLFWwindow* window) : m_window(window) {};
    void run();
private:
    GLFWwindow* m_window;
};


#endif //FACERIG_RENDER_H
