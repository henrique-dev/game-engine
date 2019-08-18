#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H
//#define GLFW_INCLUDE_GLCOREARB

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <texture.h>
#include <shader.h>


class SpriteRenderer
{
public:
    // Constructor (inits shaders/shapes)
    SpriteRenderer(Texture2D &texture, Shader &shader, glm::vec4 position);
    // Destructor
    ~SpriteRenderer();
    // Renders a defined quad textured with given sprite
    void drawSprite(glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, bool inverted = false, glm::vec3 color = glm::vec3(1.0f));

    Shader &getShader();
protected:
    // Render state
    Texture2D texture;
    Shader shader;
    glm::vec4 position;
private:
    GLuint quadVAO;
    GLuint quadVAOi;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};

#endif
