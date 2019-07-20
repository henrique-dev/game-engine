#ifndef SPRITEUTILS_H
#define SPRITEUTILS_H
#include <vector>
#include <sprite.h>

class SpriteUtils
{
    public:
        SpriteUtils();
        virtual ~SpriteUtils();

        static std::vector<Sprite*> * generateSpriteFromTexture(Texture2D& texture, int rows, int cols, int offset, int qtd);

    protected:

    private:
};

#endif // SPRITEUTILS_H
