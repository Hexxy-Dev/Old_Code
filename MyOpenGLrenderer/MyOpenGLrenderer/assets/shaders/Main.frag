#version 330 core

//layout(location = 0) out vec3 FragColor;
out vec3 FragColor;

in vec2 TexCoord;

uniform sampler2D RenderedTexture;

void main()
{
    vec3 color = texture(RenderedTexture, TexCoord).rgb;

    FragColor = color;
    FragColor = vec3(1.0, 1.0, 1.0);
}