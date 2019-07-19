#ifndef ENTITY_H
#define ENTITY_H
#include <vector2d.h>

using namespace math;

class Entity
{
    public:
        Entity(float x, float y, float width, float height);
        Entity(Entity& entity);
        virtual ~Entity();

    protected:

    private:
        Vector2D pos, width, height;
};

#endif // ENTITY_H
