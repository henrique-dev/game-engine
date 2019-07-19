#version 330 core
in vec4 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
    color = vec4(spriteColor, 1.0) * texture(image, vec2(TexCoords.z, TexCoords.w));
}
