#ifndef TILE_H
#define TILE_H
#include "gameentity.h"

class Tile : public GameEntity
{
public:
	Tile(float x, float y, float width, float height, std::string firstSpriteAnimation);
	virtual ~Tile();

	void draw();
	void update(float dt, float t);
	void invert(bool invert);

	bool debug = true;

	virtual void setCollisionBox(CollisionBox collisionBox);

protected:

private:
};

#endif // TILE_H
