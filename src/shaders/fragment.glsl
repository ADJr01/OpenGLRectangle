#version 410
layout(location = 0) out vec4 color;
in vec3 positional_data;
uniform float time;
float waveColor(float channel,float wave_to_channel,float time){
    int time_decimal = int(time * 10) % 10;
    return ((time_decimal%2)==0)? (channel * sin(time))/wave_to_channel:(channel * cos(-time))/wave_to_channel;
}
void main(){
    float x_mid = positional_data.x;
    float y_mid = positional_data.y;
    float z_mid = positional_data.z/2;
    float phi_time = (time/0.613);
    float red_channel_data = waveColor(x_mid,y_mid,phi_time)/phi_time;
    float r = red_channel_data<0.11?0.12:red_channel_data;
    float g = waveColor(y_mid,x_mid,phi_time);
    float b = waveColor(x_mid,y_mid,phi_time); // we're passing blue color to x axis
    color = vec4(r,g,b,1.0);
}