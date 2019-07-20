#include "spriteutils.h"

SpriteUtils::SpriteUtils()
{
    //ctor
}

SpriteUtils::~SpriteUtils()
{
    //dtor
}

std::vector<Sprite*> * SpriteUtils::generateSpriteFromTexture(Texture2D& texture, int rows, int cols, int offset, int qtd)
{
    std::vector<Sprite*> * sprites = new std::vector<Sprite*>();
    float width = texture.width / cols;
    float height = texture.height / rows;
    int c = 0, index = 0;
    bool startCollect = offset > 0 ? false : true;
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            c++;
            float posX = j * width;
            float posY = i * height;
            if (startCollect) sprites->push_back(new Sprite(texture, ResourceManager::getShader("sprite"), posX, posY, width, height));
            if (c >= qtd)
                return sprites;
            index++;
            if (index == offset) startCollect = true;
        }
    }
    //std::cout << "qtd: " << sprites->size() << std::endl;
    return sprites;
}
