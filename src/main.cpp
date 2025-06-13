#include <cstring>
#include <iostream>
#include <memory>
#include "GLX/Glx.h"

std::string vertex_shader = R"(
#version 410
layout(location=0) in vec3 pos;
out vec3 positional_data;
void main(){
    gl_Position = vec4(pos,1.0);
    positional_data=pos;
}
)";

std::string fragment_shader = R"(
#version 410
out vec4 color;
in vec3 positional_data;
uniform float time;
void main(){
    float phi_time = time/0.61;
    float r = cos(positional_data.x*phi_time);
    float g = sin(positional_data.y*phi_time);
    float b = cos(positional_data.z*phi_time);
    color = vec4(r,g,b,1.0);
}
)";

unsigned int compileShader(std::string& shader_src,unsigned int shader_type);
unsigned int createShaderProgram(std::string& vertex_shader,std::string& fragment_shader);
unsigned int vao,vbo,program;
int main() {
    auto glx = std::make_unique<GLX>();

    glx->setWindowTitle("Rectangle");
    glx->setWindowWidth(glx->glx_primary_monitor_width());
    glx->setWindowHeight(glx->glx_primary_monitor_height());

    glx->addPostLaunchProcedure([]() {

        float vertex_data[] = {
            -0.8f,0.8f,0.0f,
            0.8f,0.8f,0.0f,
            -0.8f,-0.8f,0.0f,
            0.8f,0.8f,0.0f,
            -0.8f,-0.8f,0.0f,
            0.8f,-0.8f,0.0f,
        };
        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);
        //buffer
        glGenBuffers(1,&vbo);
        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glBufferData(GL_ARRAY_BUFFER,sizeof(float)*18,vertex_data,GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
        glEnableVertexAttribArray(0);
        program = createShaderProgram(vertex_shader,fragment_shader);
        glUseProgram(program);
        glBindVertexArray(vao);

    });


    glx->onTick([] {
        float time = glfwGetTime();
        auto time_ptr = glGetUniformLocation(program,"time");
        glUniform1f(time_ptr,time);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES,0,6);

    });
    glx->launch();
}

unsigned int compileShader(std::string& shader_src,unsigned int shader_type) {
    unsigned int shader = glCreateShader(shader_type);
    char* src_ptr[1];
    src_ptr[0] = &shader_src[0];
    int src_len[1];
    src_len[0] = static_cast<int>(strlen(src_ptr[0]));
    glShaderSource(shader,1,src_ptr,src_len);
    glCompileShader(shader);
    int compile_status;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&compile_status);
    if (compile_status==GL_FALSE)
    {
        int length = 0;
        glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&length);
        char* info_log = static_cast<char*>(alloca(sizeof(char) * length));
        glGetShaderInfoLog(shader,length,&length,info_log);
        std::cout<<"Error while tried to compile "<<(shader_type==GL_VERTEX_SHADER?"Vertex":"Fragment")<<" Shader:\n" << info_log << '\n';
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
unsigned int createShaderProgram(std::string& vertex_shader,std::string& fragment_shader) {
    unsigned int program = glCreateProgram();
    unsigned int Vs = compileShader(vertex_shader,GL_VERTEX_SHADER);
    unsigned int Fs = compileShader(fragment_shader,GL_FRAGMENT_SHADER);
    if(Vs == 0 || Fs == 0) {
        std::cout<<"Failed To Compile Shader\n";
        return 0;
    }
    glAttachShader(program,Vs);
    glAttachShader(program,Fs);
    glLinkProgram(program);
    glValidateProgram(program);
    return program;
}