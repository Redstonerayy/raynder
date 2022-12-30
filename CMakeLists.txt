CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

project(raynder)

# get .c/.cpp files
file(GLOB_RECURSE CPP_FILES LIST_DIRECTORIES false src/*.c??)

# get .h/.hpp files
file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false src/*.h??)

add_executable(raynder ${CPP_FILES} ${HEADER_FILES})
