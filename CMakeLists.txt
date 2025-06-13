cmake_minimum_required(VERSION 3.16)
project(OpenGlRectangle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use pkg‐config to find glew and glfw3
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

# Single executable
add_executable(OpenGlRectangle src/main.cpp src/GLX/Glx.cpp src/GLX/GLSLX/GlslX.cpp)

# Tell CMake where to find the headers
target_include_directories(OpenGlRectangle PRIVATE
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
)

# And where to find the libraries
target_link_directories(OpenGlRectangle PRIVATE
        ${GLEW_LIBRARY_DIRS}
        ${GLFW_LIBRARY_DIRS}
)

# Link in GLEW, GLFW and the system OpenGL
target_link_libraries(OpenGlRectangle PRIVATE
        ${GLEW_LIBRARIES}
        ${GLFW_LIBRARIES}
        GL
)

