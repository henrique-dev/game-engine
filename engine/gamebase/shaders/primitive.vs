#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec4 TexCoords;

uniform mat4 model2;
uniform mat4 view2;
uniform mat4 projection2;

void main()
{
    TexCoords = vec4(vertex.x, vertex.y, 0.0, 1.0);
    //gl_Position = projection2 * view2 * model2 * vec4(vertex.x, vertex.y, 0.0, 1.0);
    gl_Position = projection2 * view2 * model2 * vec4(vertex.x, vertex.y, 0.0, 1.0);
}
