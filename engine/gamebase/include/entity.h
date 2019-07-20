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

        virtual void setX(float x);
        virtual void setY(float y);
        virtual void setWidth(float width);
        virtual void setHeight(float height);

        virtual float getX() const;
        virtual float getY() const;
        virtual float getWidth() const;
        virtual float getHeight() const;

        virtual void update(float dt, float t);

    protected:
        Vector2D pos, width, height;
    private:

};

#endif // ENTITY_H
