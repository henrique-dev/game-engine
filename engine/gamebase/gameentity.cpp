#include "gameentity.h"

GameEntity::GameEntity(float x, float y, float width, float height) : Entity(x, y, width, height)
{
	//ctor
}

GameEntity::~GameEntity()
{
	//delete this->sprites;
}

void GameEntity::update(float dt)
{

}

void GameEntity::draw()
{
	//this->sprites->at(this->currentSprite)->draw(getX(), getY(), getWidth(), getHeight(), 0.0f, this->invertSprite, 1.0f, 1.0f, 1.0f);
}

void GameEntity::setSpritesAnimation(std::string name, SpriteAnimation* spriteAnimation)
{
	this->spritesAnimation[name] = spriteAnimation;
}

void GameEntity::setCurrentSpriteAnimation(std::string name)
{
	this->currentSpriteAnimation = name;
}

SpriteAnimation* GameEntity::getCurrentSpriteAnimation()
{
	return this->spritesAnimation[this->currentSpriteAnimation];
}

void GameEntity::setX(float x)
{
	this->pos.x = x;
}

void GameEntity::setY(float y)
{
	this->pos.y = y;
}

glm::vec2 GameEntity::getPos() const
{
	return this->pos;
}

glm::vec2 GameEntity::getSize() const
{
	return this->size;
}

CollisionBox GameEntity::getCollisionBox(std::string name)
{
	return this->collisionBox[name];
}
