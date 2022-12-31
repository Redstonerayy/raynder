#include "shaderloader.hpp"

#include "headers/stl.hpp"
#include "util/util.hpp"

#include <glad/glad.h>
#include <fstream>

namespace OpenGL {

ShaderLoader::ShaderLoader(std::vector<std::string> directories, std::vector<std::string> paths){
    // get all filepaths from each directory
    for( std::string directory : directories ){
        this->GetPathFromDirectory(directory);        
    };
    // load all shaders
    for( std::string path : this->paths ){
        this->LoadShaderFromFile(path);
    };
}

ShaderLoader::~ShaderLoader(){
    // free all memory, delete all shaders and programs
    // delete programs
    for( GLuint program : this->programs ){
        glDeleteProgram(program);
    }
    // delete shaders
    for( const auto & [ key, value ] : this->shaders ){
        glDeleteShader(value.shaderid);
    }
}

GLuint ShaderLoader::MakeProgram(std::vector<std::string> shadernames, bool use=false){
    // create program
    const GLuint program = glCreateProgram();
    // store to delete it in destructor
    this->programs.emplace_back(program);
    // link the shaders which match the name
    for( std::string shader : shadernames ){
        if(this->shaders.count(shader) == 1){
            glAttachShader(program, this->shaders[shader].shaderid);
        } else {
            std::cout << "ERROR: Shader " << shader << " not present!" << std::endl;
        }
    }
    // link program and return, specify if it should be used
    glLinkProgram(program);
    if( use ) glUseProgram(program);
    return program;
}

void ShaderLoader::LoadShaderFromFile(std::string path){
    // try to open file
    std::ifstream file(path);
    // abort and return on error
    if( ! file.is_open() ) return;
    // read file
    std::string content( (std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>() );
    // create shader
    // find out which type of shader
    std::vector<std::string> parts = SplitString(path, "_");
    std::string name = std::filesystem::path(path).filename();
    std::string type = SplitString(parts.at(parts.size() - 1), ".").at(0);
    GLuint shader;
    // create shader with right type
    if( type == "vertex"){
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    if( type == "fragment"){
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }
    // compile the shader source
    const char* shadersource = content.c_str();
    glShaderSource(shader, 1, &shadersource, nullptr);
    glCompileShader(shader);
    // check for compile error https://www.khronos.org/opengl/wiki/Shader_Compilation
    // check for error
    GLint iscompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &iscompiled);
    // log error
    if( iscompiled == GL_FALSE ){
        GLint maxlength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxlength);

        // The maxlength includes the NULL character
        std::vector<GLchar> errorlog(maxlength);
        glGetShaderInfoLog(shader, maxlength, &maxlength, &errorlog[0]);

        std::cout << std::string(errorlog.begin(), errorlog.end()) << std::endl;

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(shader); // Don't leak the shader.
        return;
    }
    // add into hashmap
    this->shaders[name] = (Shader{shader, path, name});
}

void ShaderLoader::GetPathFromDirectory(std::string directory){
    // for each file in the directory add it to the global paths list if the path is not present yet
    for( const auto & entry : std::filesystem::directory_iterator(directory) ){
        std::string path = entry.path();
        if( ! std::any_of( this->paths.begin(), this->paths.end(), [path](std::string existingpath){ return existingpath == path;} ) ){
            this->paths.emplace_back(path);
        }
    }
}

}
