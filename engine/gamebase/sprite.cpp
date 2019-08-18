#include "sprite.h"
#include <iostream>

Sprite::Sprite(Texture2D& texture, Shader& shader,
	float x, float y, float width, float height) : SpriteRenderer(texture, shader, glm::vec4(x, y, width, height))
{

}

Sprite::~Sprite()
{
	//dtor
}

void Sprite::draw(float x, float y, float width, float height, float degress, bool inverted, float r, float g, float b)
{
	this->drawSprite(glm::vec2(x, y), glm::vec2(width, height), degress, inverted, glm::vec3(r, g, b));
}
