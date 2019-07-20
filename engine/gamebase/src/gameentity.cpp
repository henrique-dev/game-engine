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

float GameEntity::getX() const
{
    return this->pos.x;
}

float GameEntity::getY() const
{
    return this->pos.y;
}
