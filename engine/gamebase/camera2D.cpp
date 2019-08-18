#include "camera2d.h"
#include "resource_manager.h"

Camera2D::Camera2D(float x, float y, float width, float height, float xs, float ys, Shader& shader) : Entity(x, y, width, height), shader(shader)
{
	this->initCamera();
	this->pos.x = xs;
	this->pos.y = ys;
}

Camera2D::~Camera2D()
{
	//dtor
}

void Camera2D::setTarget(GameEntity* target)
{
	this->target = target;
}

void Camera2D::update()
{
	//this->pos += Vector2D(x, y);
	float x = this->target->getPos().x - 500;
	float y = this->target->getPos().y - 200;
	this->pos.y = -y;
	this->pos.x = -x;
	glm::mat4 view = glm::lookAt(this->cameraPos, this->cameraFront, this->cameraUp);
	view = glm::translate(view, glm::vec3(this->pos.x, this->pos.y, 0));

	this->shader.Use();
	this->shader.SetMatrix4("view", view);

	ResourceManager::getShader("primitive").Use();
	ResourceManager::getShader("primitive").SetMatrix4("view2", view);
}

void Camera2D::initCamera()
{
	this->shader.Use();
	this->cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	this->cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::lookAt(this->cameraPos, this->cameraFront, this->cameraUp);
	view = glm::translate(view, glm::vec3(this->pos.x, this->pos.y, 0));

	this->shader.SetMatrix4("view", view);

	ResourceManager::getShader("primitive").Use();
	ResourceManager::getShader("primitive").SetMatrix4("view2", view);
}
