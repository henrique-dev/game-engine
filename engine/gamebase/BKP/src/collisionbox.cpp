#include "collisionbox.h"
#include <iostream>
#include <resource_manager.h>

CollisionBox::CollisionBox(float x, float y, float width, float height)
{
    this->pos = glm::vec2(x,y);
    this->size = glm::vec2(width, height);
}

CollisionBox::~CollisionBox()
{
    //dtor
}

void CollisionBox::init(Shader &shader)
{
    this->shader = shader;

    GLuint VBO;

    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, // TOP LEFT
        1.0f, 0.0f, // BOTTOM RIGHT
        0.0f, 0.0f, // BOTTOM LEFT

        0.0f, 1.0f, // TOP LEFT
        1.0f, 1.0f, // TOP RIGHT
        1.0f, 0.0f  // BOTTOM RIGHT
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CollisionBox::draw()
{
    // Prepare transformations
    this->shader.Use();
    //glm::mat4 model;
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(this->pos.x, this->pos.y, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * this->size.x, 0.5f * this->size.y, 0.0f)); // Move origin of rotation to center of quad
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
    model = glm::translate(model, glm::vec3(-0.5f * this->size.x, -0.5f * this->size.y, 0.0f)); // Move origin back

    model = glm::scale(model, glm::vec3(this->size.x, this->size.y, 1.0f)); // Last scale

    this->shader.SetMatrix4("model2", model);

    // Render textured quad
    this->shader.SetVector3f("spriteColor2", glm::vec3(1.0f, 0.0f, 0.0f));

    //glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void CollisionBox::setX(float x)
{
    this->pos.x = x;
}

void CollisionBox::setY(float y)
{
    this->pos.y = y;
}

glm::vec2 CollisionBox::getPos() const
{
    return this->pos;
}

glm::vec2 CollisionBox::getSize() const
{
    return this->size;
}
