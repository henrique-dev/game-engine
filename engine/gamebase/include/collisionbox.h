#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H
#include <shader.h>

class CollisionBox
{
    public:
        CollisionBox(float x, float y, float width, float height);
        virtual ~CollisionBox();

        void init(Shader &shader);
        void draw();

        void set(float x, float y);
        float getX() const;

    protected:
        Shader shader;
        glm::vec4 position;

    private:
        float x, y, width, height;
        GLuint quadVAO;
        GLuint quadVAOi;

};

#endif // COLLISIONBOX_H
