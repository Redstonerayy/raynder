#pragma once

#pragma once

#include "headers/stl.hpp"

#include <glad/glad.h>

namespace OpenGL {

struct Shader {
    GLuint shaderid;
    std::string path;
    std::string name;
};

class ShaderLoader {
public:
    ShaderLoader(std::vector<std::string> directories, std::vector<std::string> paths);
    ~ShaderLoader();
    GLuint MakeProgram(std::vector<std::string> shadernames, bool use);
private:
    std::vector<std::string> paths;
    std::unordered_map<std::string, Shader> shaders;
    std::vector<GLuint> programs;
    void LoadShaderFromFile(std::string path);
    void GetPathFromDirectory(std::string directory);
};

}
