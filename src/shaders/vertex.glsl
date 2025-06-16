#version 410
layout(location=0) in vec3 pos;
out vec3 positional_data;
void main(){
    float x = sin(pos.x);
    float y = tan(pos.y);
    gl_Position = vec4(x,y,0.0,1.0);
    positional_data=vec3(x,y,0.0);
}