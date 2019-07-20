#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H
#include <sprite.h>
#include <vector>

class SpriteAnimation
{
    public:
        SpriteAnimation(std::vector<Sprite*>* sprites, int step);
        SpriteAnimation(std::vector<Sprite*>* sprites, std::vector<Sprite*>* spritesLayer2, int step);
        virtual ~SpriteAnimation();

        void animate();
        void draw(float x, float y, float width, float height, float degress, bool inverted, float r, float g, float b);
        Sprite* getCurrentSprite() const;
        std::vector<Sprite*>* getSprites() const;

    protected:

    private:
        int currentSprite = 0;
        int step;
        std::vector<Sprite*>* sprites;
        std::vector<Sprite*>* spritesLayer2 = nullptr;
};

#endif // SPRITEANIMATION_H
