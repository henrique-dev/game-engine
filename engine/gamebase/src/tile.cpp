#include "tile.h"

Tile::Tile(float x, float y, float width, float height, std::string firstSpriteAnimation) : GameEntity(x, y, width, height)
{
    this->currentSpriteAnimation = firstSpriteAnimation;
}

Tile::~Tile()
{
    //dtor
}

void Tile::update(float dt, float t)
{
    this->getCurrentSpriteAnimation()->animate();
}

void Tile::invert(bool invert)
{
    this->invertSprite = invert;
}

void Tile::draw()
{
    this->getCurrentSpriteAnimation()->draw(getX(), getY(), getWidth(), getHeight(), 0.0f, this->invertSprite, 1.0f, 1.0f, 1.0f);
}
