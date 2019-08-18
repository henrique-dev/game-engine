#ifndef SPRITE_H
#define SPRITE_H
#include <spriterenderer.h>
#include <vector>
#include <texture.h>
#include<resource_manager.h>

class Sprite : public SpriteRenderer
{
    public:
        Sprite(Texture2D &texture, Shader &shader, float x, float y, float width, float height);
        virtual ~Sprite();

        void draw(float x, float y, float width, float height, float degress, bool inverted, float r, float g, float b);

    protected:

    private:
};

#endif // SPRITE_H
