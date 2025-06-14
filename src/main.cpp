#include <cstring>
#include <iostream>
#include <memory>
#include "GLX/Glx.h"



std::string frag_src = "/home/adnan/Desktop/Projects/Cpp/CG/OpenGlRectangle/src/shaders/fragment.glsl";
std::string vert_src = "/home/adnan/Desktop/Projects/Cpp/CG/OpenGlRectangle/src/shaders/vertex.glsl";

unsigned int vao,vbo;
int main() {
    GLX glx;
    auto shaderTool = glx.ShaderTool();
    glx.setWindowTitle("Rectangle");
    glx.setWindowWidth(glx.glx_primary_monitor_width());
    glx.setWindowHeight(glx.glx_primary_monitor_height());
    glx.addPostLaunchProcedure([&glx]() {
        float vertex_data[] = {
            -0.8f,0.8f,0.0f,
            0.8f,0.8f,0.0f,
            -0.8f,-0.8f,0.0f,
            0.8f,0.8f,0.0f,
            -0.8f,-0.8f,0.0f,
            0.8f,-0.8f,0.0f,
        };

        glx.ShaderTool().setVertexShaderPath("/home/adnan/Desktop/Projects/Cpp/CG/OpenGlRectangle/src/shaders/vertex.glsl");
        glx.ShaderTool().setFragmentShaderPath("/home/adnan/Desktop/Projects/Cpp/CG/OpenGlRectangle/src/shaders/fragment.glsl");
        glx.ShaderTool().buildProgram();
        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);
        //buffer
        glGenBuffers(1,&vbo);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferData(GL_ARRAY_BUFFER,sizeof(float)*18,vertex_data,GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(vao);
        glUseProgram(glx.ShaderTool().getProgram());


    });


    glx.onTick([&glx] {

        float time = glfwGetTime();
        auto time_ptr = glGetUniformLocation(glx.ShaderTool().getProgram(),"time");
        glUniform1f(time_ptr,time);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES,0,6);

    });
    glx.launch();
}


