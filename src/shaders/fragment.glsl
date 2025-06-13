#version 410
layout(location = 0) out vec4 color;
in vec3 positional_data;
uniform float time;
void main(){
    float phi_time = time/0.61;
    float r = cos(positional_data.x*phi_time);
    float g = sin(positional_data.y*phi_time);
    float b = cos(positional_data.z*phi_time);
    color = vec4(r,g,b,1.0);
}