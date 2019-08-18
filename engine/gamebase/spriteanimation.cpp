#include "spriteanimation.h"

SpriteAnimation::SpriteAnimation(std::vector<Sprite*>* sprites, int step) : sprites(sprites), step(step) {}

SpriteAnimation::SpriteAnimation(std::vector<Sprite*>* sprites, std::vector<Sprite*>* spritesLayer2, int step) : sprites(sprites), spritesLayer2(spritesLayer2), step(step) {}

SpriteAnimation::~SpriteAnimation()
{
	//dtor
}

void SpriteAnimation::animate()
{
	this->currentSprite++;
	if (this->currentSprite >= this->sprites->size() * this->step)
		this->currentSprite = 0;
}

void SpriteAnimation::draw(float x, float y, float width, float height, float degress, bool inverted, float r, float g, float b)
{
	this->sprites->at(this->currentSprite / this->step)->draw(x, y, width, height, degress, inverted, r, g, b);
	if (this->spritesLayer2 != nullptr)
	{
		this->spritesLayer2->at(this->currentSprite / this->step)->draw(x, y, width, height, degress, inverted, r, g, b);
	}
}

Sprite* SpriteAnimation::getCurrentSprite() const
{
	return this->sprites->at(this->currentSprite / this->step);
}

std::vector<Sprite*>* SpriteAnimation::getSprites() const
{
	return this->sprites;
}
