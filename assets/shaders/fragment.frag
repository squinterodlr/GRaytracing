#version 430

in vec4 vertexColor;
in vec2 texCoord;


out vec4 FragColor;

uniform sampler2D theTexture;

void main()
{
    vec3 texCol = texture(theTexture, texCoord).rgb;
    FragColor = vec4(texCol, 1.0);
}