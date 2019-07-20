#ifndef CREATURE_H
#define CREATURE_H
#include <gameentity.h>
#include <vector2d.h>

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

        void move(float x, float y);
        void jump(float time, float speed);
        bool checkGroundCollision(float x, float y, float width);
        void setCurrentState(CreatureState state);
        CreatureState getCurrentState() const;

    protected:

    private:
        CreatureState currentState = FALLING;
        float jumpTime = 0;
        Vector2D speed = Vector2D(0,0);
        float gravity = 15.0f;

};

#endif // CREATURE_H
