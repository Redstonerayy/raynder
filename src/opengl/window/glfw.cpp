#include "glfw.hpp"

// tell glfw to not include glad. needed if glad is included after glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>

namespace OpenGL {

void GLFW_Init(int openglmajor, int openglminor) {
    // set callbacks for glfw library
    glfwSetErrorCallback([](int error, const char* description) {
        fprintf(stderr, "Error: %s\n", description);
    });
    // initialize window with OpenGL Version 4.6 and Core Profile
    if( !glfwInit() )
        exit(EXIT_FAILURE);
    // window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openglmajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openglminor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GLFW_Terminate(GLFWwindow * window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

}
