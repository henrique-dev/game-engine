#include "entity.h"

Entity::Entity(Entity& entity)
{
	this->pos.x = entity.pos.x;
	this->pos.y = entity.pos.y;
	this->size.x = entity.size.x;
	this->size.y = entity.size.y;
}

Entity::Entity(float x, float y, float width, float height)
{
	this->pos = glm::vec2(x, y);
	this->size = glm::vec2(width, height);
}

Entity::~Entity()
{
	//dtor
}

void Entity::update(float dt, float t)
{

}

void Entity::setX(float x)
{
	this->pos.x = x;
}

void Entity::setY(float y)
{
	this->pos.y = y;
}

CollisionBox Entity::getCollisionBox(std::string name)
{
	return this->collisionBox[name];
}

void Entity::setCollisionBox(CollisionBox collisionBox, std::string name)
{
	this->collisionBox[name] = collisionBox;
	this->collisionBox[name].init(ResourceManager::getShader("primitive"));
}

void Entity::setCollisionBox(std::map<std::string, CollisionBox> colls)
{
	this->collisionBox = colls;
}
