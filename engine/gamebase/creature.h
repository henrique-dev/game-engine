#ifndef CREATURE_H
#define CREATURE_H
#include "gameentity.h"
#include "collisionbox.h"

enum CreatureState {
	RUNNING,
	JUMPING,
	IDLE,
	FALLING
};

class Creature : public GameEntity
{
public:
	Creature(float x, float y, float width, float height, std::string firstSpriteAnimation);
	virtual ~Creature();

	void draw();
	void update(float dt, float t);
	void invert(bool invert);

	void setX(float x);
	void setY(float y);

	void move(float x, float y);
	void jump(float time, float speed);
	//std::vector<Vector2D> checkCollision(CollisionBox box);
	void setCurrentState(CreatureState state);
	CreatureState getCurrentState() const;

	void setCollisionBox(CollisionBox collisionBox, std::string name);
	void setCollisionBox(std::map<std::string, CollisionBox>);

protected:

private:
	CreatureState currentState = FALLING;
	float jumpTime = 0;
	glm::vec2 speed = glm::vec2(0, 0);
	float gravity = 15.0f;

	void updateCollisionBox();

};

#endif // CREATURE_H
