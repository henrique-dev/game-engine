#version 330 core
in vec4 TexCoords;
out vec4 color;

uniform sampler2D image2;
uniform vec3 spriteColor2;

void main()
{
    color = vec4(spriteColor2, 1.0) * texture(image2, vec2(TexCoords.z, TexCoords.w));
    //color = vec4(1.0f, 1.0f, 0.2f, 1.0f);
}
