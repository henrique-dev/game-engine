#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec4 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoords = vec4(vertex.z, vertex.w, vertex.z, vertex.w);
    gl_Position = projection * model * vec4(vertex.x, vertex.y, 0.0, 1.0);
}
