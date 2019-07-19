#include <sprite.h>
#include <iostream>

Sprite::Sprite(Texture2D &texture, Shader &shader,
    float x, float y, float width, float height) : SpriteRenderer(texture, shader, glm::vec4(x, y, width, height))
{

}

Sprite::~Sprite()
{
    //dtor
}

void Sprite::draw(float x, float y, float width, float height, float degress, float r, float g, float b)
{
    this->drawSprite(glm::vec2(x, y), glm::vec2(width, height), degress, glm::vec3(r, g, b));
}

void Sprite::printInfo()
{
    std::cout << this->position.x << " - " << this->position.y << " ## " << this->position.w << " - " << this->position.z << std::endl;
}

std::vector<Sprite*> * Sprite::generateSpriteFromTexture(Texture2D& texture, int rows, int cols, int qtd)
{
    std::vector<Sprite*> * sprites = new std::vector<Sprite*>;
    std::vector<Sprite*>::iterator it;
    it = sprites->begin();
    float width = texture.width / cols;
    float height = texture.height / rows;
    int c = 0;
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            float posX = j * width;
            float posY = i * height;
            //std::cout << width << " - " << height << std::endl;
            //std::cout << posX << " - " << posY << std::endl;
            it = sprites->insert(it, new Sprite(texture,
                ResourceManager::getShader("sprite"), posX, posY, width, height));
            if (c > qtd)
                break;
        }
        if (c > qtd)
            break;
        c++;
    }
    //std::cout << "qtd: " << sprites->size() << std::endl;
    return sprites;
}
