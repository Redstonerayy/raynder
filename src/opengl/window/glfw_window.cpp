#include "glfw_window.hpp"

// tell glfw to not include glad. needed if glad is included after glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstdlib>

namespace OpenGL {

GLFWwindow* GLFW_WindowInitOpenGL(){
    // create window object
    GLFWwindow* window = glfwCreateWindow(
        1024, 768, "Raynder", nullptr, nullptr
    );
    // check if creation worked
    if(!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    // set callbacks for window
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
        if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });
    // assign context to window
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    return window;
}

}