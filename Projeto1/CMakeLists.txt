cmake_minimum_required(VERSION 3.10)
project(Projeto1-ComputacaoGrafica)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(montanha.o montanha-russa.cpp)

target_link_libraries(montanha.o
    PRIVATE
    OpenGL::GL      
    OpenGL::GLU
    GLUT::GLUT
    m
)
include(CTestUseLaunchers)
