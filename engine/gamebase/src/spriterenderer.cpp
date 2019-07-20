#define GLFW_INCLUDE_GLCOREARB
#include <spriterenderer.h>
#include <iostream>
#include <math.h>

SpriteRenderer::SpriteRenderer(Texture2D &texture, Shader &shader, glm::vec4 position)
{
    this->texture = texture;
    this->shader = shader;
    this->position = position;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::drawSprite(glm::vec2 position, glm::vec2 size, GLfloat rotate, bool inverted, glm::vec3 color)
{
    // Prepare transformations
    this->shader.Use();
    //glm::mat4 model;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    this->shader.SetMatrix4("model", model);

    // Render textured quad
    this->shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    this->texture.bind();

    if (inverted) glBindVertexArray(this->quadVAOi);
    else glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    // Configure VAO/VBO
    GLuint VBO;
    GLfloat perW = 1 / (float)this->texture.width;
    GLfloat perH = 1 / (float)this->texture.height;

    float top_left_x = (float)this->position.x * perW;
    float top_left_y = 1 - (float)this->position.y * perH;

    float top_right_x = ((float)this->position.x * perW + (float)this->position.z * perW);
    float top_right_y = 1 - (float)this->position.y * perH;

    float bottom_left_x = (float)this->position.x * perW;
    float bottom_left_y = 1 - ((float)this->position.y + (float)this->position.w) * perH;

    float bottom_right_x = ((float)this->position.x + (float)this->position.z) * perW;
    float bottom_right_y = 1 - ((float)this->position.y + (float)this->position.w) * perH;

    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, top_left_x, top_left_y,          // TOP LEFT
        1.0f, 0.0f, bottom_right_x, bottom_right_y,  // BOTTOM RIGHT
        0.0f, 0.0f, bottom_left_x, bottom_left_y,    // BOTTOM LEFT

        0.0f, 1.0f, top_left_x, top_left_y,          // TOP LEFT
        1.0f, 1.0f, top_right_x, top_right_y,        // TOP RIGHT
        1.0f, 0.0f, bottom_right_x, bottom_right_y  // BOTTOM RIGHT
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // INVERTED
    GLfloat verticesi[] = {
        // Pos      // Tex
        0.0f, 1.0f, top_right_x, top_right_y,        // TOP RIGHT
        1.0f, 0.0f, bottom_left_x, bottom_left_y,    // BOTTOM LEFT
        0.0f, 0.0f, bottom_right_x, bottom_right_y,  // BOTTOM RIGHT

        0.0f, 1.0f, top_right_x, top_right_y,        // TOP RIGHT
        1.0f, 1.0f, top_left_x, top_left_y,          // TOP LEFT
        1.0f, 0.0f, bottom_left_x, bottom_left_y,    // BOTTOM LEFT
    };

    glGenVertexArrays(1, &this->quadVAOi);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesi), verticesi, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAOi);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
