#ifndef CAMERA2D_H
#define CAMERA2D_H
#include <shader.h>
#include <entity.h>
#include <gameentity.h>
#include <shader.h>

class Camera2D : public Entity
{
    public:
        Camera2D(float x, float y, float width, float height, float xs, float ys, Shader &shader);
        virtual ~Camera2D();

        void setTarget(GameEntity * target);
        void update();

    protected:
        Shader shader;
    private:
        glm::vec3 cameraPos;
        glm::vec3 cameraUp;
        glm::vec3 cameraFront;
        GameEntity * target;

        void initCamera();

};

#endif // CAMERA2D_H
