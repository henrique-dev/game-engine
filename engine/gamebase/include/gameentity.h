#ifndef GAMEENTITY_H
#define GAMEENTITY_H
#include <entity.h>
#include <sprite.h>

class GameEntity : public Entity
{
    public:
        GameEntity(Entity& entity);
        virtual ~GameEntity();

    protected:

    private:
        Sprite* sprite[];
};

#endif // GAMEENTITY_H
