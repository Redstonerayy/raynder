#include "headers/glm.hpp"
#include "headers/stl.hpp"
#include "headers/opengl.hpp"
#include "opengl/shader/shaderloader.hpp"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace gl = OpenGL;

int main( void ){
    // initialize window and OpenGL
    gl::GLFW_Init(4, 6);
    GLFWwindow* window = gl::GLFW_WindowInitOpenGL();
    gladLoadGL();
    // get shaders and make program
    std::string cwd = std::filesystem::current_path();
    gl::ShaderLoader shaderloader({ cwd + "/src/shaders"}, {});
    const GLuint program = shaderloader.MakeProgram({ "simple_fragment.glsl", "simple_vertex.glsl"}, true);
    // create empty vao
    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // glfw window hints
    // MSAA, set windowhint in glfw create function
    glEnable(GL_MULTISAMPLE);
    
    while( !glfwWindowShouldClose(window) ){

        // window resizing
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        // matrices
        const float ratio = width / (float) height;
        const glm::mat4 m = glm::rotate(
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.5f)),
            (float)glfwGetTime(),
            glm::vec3(1.0f, 1.0f, 1.0f)
        );
        const glm::mat4 p = glm::perspective(45.0f, ratio, 0.1f, 1000.0f);
        // solid background
        glClear(GL_COLOR_BUFFER_BIT);
        // draw and swap buffers, events
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glDeleteVertexArrays(1, &vao);
    
    gl::GLFW_Terminate(window);

    return 0;
}
