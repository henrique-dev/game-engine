#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H
#include <shader.h>

class CollisionBox
{
    public:
        CollisionBox(float x = 0, float y = 0, float width = 0, float height = 0);
        virtual ~CollisionBox();

        void init(Shader &shader);
        void draw();

        void setX(float x);
        void setY(float y);

        glm::vec2 getPos() const;
        glm::vec2 getSize() const;

    private:
        GLuint quadVAO;
        GLuint quadVAOi;
        Shader shader;
        glm::vec2 pos, size;

};

#endif // COLLISIONBOX_H
