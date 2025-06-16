#include <cstring>
#include <iostream>
#include <memory>
#include "GLX/Glx.h"



std::string frag_src = "/home/adnan/Desktop/Projects/Cpp/CG/OpenGlRectangle/src/shaders/fragment.glsl";
std::string vert_src = "/home/adnan/Desktop/Projects/Cpp/CG/OpenGlRectangle/src/shaders/vertex.glsl";

unsigned int vao,vbo;
int main() {
    GLX glx;
    glx.setWindowTitle("Rectangle");
    glx.setWindowWidth(800);
    glx.setWindowHeight(600);
    glx.addPostLaunchProcedure([&glx]() {
        float vertex_data[] = {
            -0.8f,0.8f,0.1f,
            0.8f,0.8f,0.2f,
            -0.8f,-0.8f,0.1f,

            0.8f,0.8f,0.2f,
            -0.8f,-0.8f,0.1f,
            0.8f,-0.8f,0.2f,
        };

        glx.ShaderTool().setVertexShaderPath(vert_src);
        glx.ShaderTool().setFragmentShaderPath(frag_src);
        glx.ShaderTool().buildProgram();
        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);
        //buffer
        glGenBuffers(1,&vbo);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferData(GL_ARRAY_BUFFER,sizeof(float)*18,vertex_data,GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
        glEnableVertexAttribArray(0);
        if (glIsVertexArray(vao)) glBindVertexArray(vao);
        glUseProgram(glx.ShaderTool().getProgram());
    });


    glx.onTick([&glx]() {

        float time = glfwGetTime();
        auto time_ptr = glGetUniformLocation(glx.ShaderTool().getProgram(),"time");
        glUniform1f(time_ptr,time);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES,0,6);


    });
    glx.launch();
}


