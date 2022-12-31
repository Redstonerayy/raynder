#pragma once

// tell glfw to not include glad. needed if glad is included after glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace OpenGL {

GLFWwindow* GLFW_WindowInitOpenGL();

}