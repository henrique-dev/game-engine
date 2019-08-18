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
	this->collisionBox["base"].setX(this->pos.x);
	this->collisionBox["base"].setY(this->pos.y);
}

void Tile::invert(bool invert)
{
	this->invertSprite = invert;
}

void Tile::draw()
{
	this->getCurrentSpriteAnimation()->draw(this->getPos().x, this->getPos().y, this->getSize().x, this->getSize().x, 0.0f, this->invertSprite, 1.0f, 1.0f, 1.0f);
	if (debug) this->collisionBox["base"].draw();
}

void Tile::setCollisionBox(CollisionBox collisionBox)
{
	this->collisionBox["base"] = collisionBox;
	this->collisionBox["base"].init(ResourceManager::getShader("primitive"));
}
