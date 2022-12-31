CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

project(raynder)

## BUILD DEPENDENCIES ##
# glfw
add_subdirectory(deps/glfw)


## BUILD APPLICATION ##
set(NAME raynder)
# set properties for compiling
set(CMAKE_CXX_FLAGS "-march=native -std=c++20")
# get .c/.cpp files from src (it is possible to get the headers with the same syntax!)
file(GLOB_RECURSE CPP_FILES LIST_DIRECTORIES false src/*.c??)
# get glad.c file
set(GLAD_FILES glad/src/glad.c)
# add executable
add_executable(${NAME} ${CPP_FILES} ${HEADER_FILES} ${GLAD_FILES})
# add include directories
target_include_directories(${NAME} PRIVATE
    src
    glad/include
    deps/glfw/include
    deps/glm
)
# link libraries
target_link_libraries(${NAME} PRIVATE
    OpenGL
    glfw
)
