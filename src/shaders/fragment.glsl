#version 410
layout(location = 0) out vec4 color;
in vec3 positional_data;
uniform float time;
float waveColor(float channel,float wave_to_channel,float time){
    return ((int(time)%2)==0)? (channel * sin(time))/wave_to_channel:(channel * cos(time))/-wave_to_channel;
}
void main(){
    float x_mid = positional_data.x/2;
    float y_mid = positional_data.y/2;
    float z_mid = positional_data.z/2;
    float phi_time = (time/0.613);
    float r = waveColor(x_mid,y_mid,phi_time);
    float g = waveColor(y_mid,z_mid,phi_time);
    float b = waveColor(y_mid,x_mid,phi_time); // we're passing blue color to x axis
    color = vec4(r,g,b,1.0);
}