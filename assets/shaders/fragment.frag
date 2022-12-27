#version 430

in vec4 vertexColor;
in vec2 texCoord;


out vec4 FragColor;

uniform sampler2D theTexture;

void main()
{
    FragColor = texture(theTexture, texCoord);
}