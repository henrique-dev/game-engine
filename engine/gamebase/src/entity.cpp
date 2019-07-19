#include "entity.h"

Entity::Entity(Entity& entity)
{
    this->pos = Vector2D(entity.pos.x, entity.pos.y);
    this->width = Vector2D(entity.width);
    this->height = Vector2D(entity.height);
}

Entity::Entity(float x, float y, float width, float height)
{
    this->pos = Vector2D(x, y);
    this->width = Vector2D(width, 0);
    this->height = Vector2D(0, height);
}

Entity::~Entity()
{
    //dtor
}
