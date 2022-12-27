#version 330 

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 inColor;

out vec4 vertexColor;
out vec2 texCoord;

const float M_PI = 3.14159265358979323846;
void main()
{
    
    vec3 modelPos = (model*vec4(pos,1.0)).xyz;
    vertexColor = (0.5*(1.0+sin(2.0*M_PI*modelPos.z)))*vec4(inColor,1.0);
    gl_Position = projection*view*model*vec4(pos,1.0);
    texCoord = tex;    
}