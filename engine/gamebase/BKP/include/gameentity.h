#ifndef GAMEENTITY_H
#define GAMEENTITY_H
#include <entity.h>
#include <sprite.h>
#include <map>
#include <spriteanimation.h>

class GameEntity : protected Entity
{
    public:
        GameEntity(float x, float y, float width, float height);
        virtual ~GameEntity();

        virtual void update(float dt);
        virtual void draw();

        void setSpritesAnimation(std::string name, SpriteAnimation* spriteAnimation);
        void setCurrentSpriteAnimation(std::string name);
        SpriteAnimation* getCurrentSpriteAnimation();

        virtual void setX(float x);
        virtual void setY(float y);

        virtual glm::vec2 getPos() const;
        virtual glm::vec2 getSize() const;
        virtual CollisionBox getCollisionBox(std::string name);

    protected:
        bool invertSprite = false;
        std::string currentSpriteAnimation;
        std::map<std::string, SpriteAnimation*> spritesAnimation;
    private:

};

#endif // GAMEENTITY_H
