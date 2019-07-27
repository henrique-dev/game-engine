#include "entity.h"

Entity::Entity(Entity& entity) : collisionBox(CollisionBox(0,0,0,0))
{
    this->pos = Vector2D(entity.pos.x, entity.pos.y);
    this->width = Vector2D(entity.width);
    this->height = Vector2D(entity.height);
}

Entity::Entity(float x, float y, float width, float height) : collisionBox(CollisionBox(0,0,0,0))
{
    this->pos = Vector2D(x, y);
    this->width = Vector2D(width, 0);
    this->height = Vector2D(0, height);
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

void Entity::setWidth(float width)
{
    this->width.x = width;
}

void Entity::setHeight(float height)
{
    this->height.y = height;
}

float Entity::getX() const
{
    return this->pos.x;
}

float Entity::getY() const
{
    return this->pos.y;
}

float Entity::getWidth() const
{
    return this->width.x;
}

float Entity::getHeight() const
{
    return this->height.y;
}

void Entity::setCollisionBox(CollisionBox collisionBox)
{
    this->collisionBox = collisionBox;
    this->collisionBox.init(ResourceManager::getShader("primitive"));
}
