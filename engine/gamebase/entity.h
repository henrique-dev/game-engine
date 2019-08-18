#ifndef ENTITY_H
#define ENTITY_H
#include "collisionbox.h"
#include "resource_manager.h"

class Entity
{
public:
	Entity(float x, float y, float width, float height);
	Entity(Entity& entity);
	virtual ~Entity();

	virtual void update(float dt, float t);

	virtual void setCollisionBox(CollisionBox collisionBox, std::string name);
	virtual void setCollisionBox(std::map<std::string, CollisionBox> colls);
	virtual void setX(float x);
	virtual void setY(float y);

	CollisionBox getCollisionBox(std::string name);
	glm::vec2 getPos() const;
	glm::vec2 getSize() const;

protected:
	glm::vec2 pos, size;
	std::map<std::string, CollisionBox> collisionBox = std::map<std::string, CollisionBox>();

};

#endif // ENTITY_H
