#ifndef CAMERA2D_H
#define CAMERA2D_H
#include <shader.h>
#include <entity.h>
#include <shader.h>

class Camera2D : public Entity
{
    public:
        Camera2D(float x, float y, float width, float height, float xs, float ys, Shader &shader);
        virtual ~Camera2D();

        void move(float x, float y);

    protected:
        Shader shader;
    private:
        glm::vec3 cameraPos;
        glm::vec3 cameraUp;
        glm::vec3 cameraFront;

        void initCamera();

};

#endif // CAMERA2D_H
