#include "creature.h"
#include <iostream>
#include <math.h>

Creature::Creature(float x, float y, float width, float height, std::string firstSpriteAnimation) : GameEntity(x, y, width, height)
{
    this->currentSpriteAnimation = firstSpriteAnimation;
}

Creature::~Creature()
{
    //dtor
}

void Creature::update(float dt, float t)
{
    if (this->currentState == JUMPING || this->currentState == FALLING)
    {
        float tempo = (t - this->jumpTime);
        this->pos += this->speed * tempo;
        this->pos.y += (this->speed.y * tempo) + (15 * (float)pow(tempo, 2)) / 2.0f;
        this->speed.y += 15 * tempo;
        this->speed.y = (this->speed.y > 10.0f) ? 10.0f : this->speed.y;
        if (this->speed.y > 0)
            this->setCurrentState(FALLING);
    }
    this->getCurrentSpriteAnimation()->animate();

    this->collisionBox.set(this->pos.x, this->pos.y);
    //this->collisionBox.set(400, 300);
    //std::cout << this->pos.x << " - " << this->collisionBox.getX() << std::endl;

}

void Creature::invert(bool invert)
{
    this->invertSprite = invert;
}

void Creature::draw()
{
    this->collisionBox.draw();
    this->getCurrentSpriteAnimation()->draw(getX(), getY(), getWidth(), getHeight(), 0.0f, this->invertSprite, 1.0f, 1.0f, 1.0f);
}

void Creature::move(float x, float y)
{
    if (x < 0) this->invert(true);
    if (x > 0) this->invert(false);
    float ix = this->getX();
    float iy = this->getY();
    this->setX( ix + x);
    this->setY( iy + y);
}
void Creature::jump(float time, float speed)
{
    this->currentState = JUMPING;
    this->jumpTime = time;
    this->speed = Vector2D(0, speed);
}

bool Creature::checkGroundCollision(float x, float y, float width)
{
    if (this->getY() + this->getHeight() >= y + 22)
    {
        this->pos.y = y - this->getHeight() + 20;
        return true;
    }
    return false;
}

void Creature::setCurrentState(CreatureState state)
{
    switch (state)
    {
        case JUMPING:
            this->setCurrentSpriteAnimation("jumping");
            break;
        case IDLE:
            this->setCurrentSpriteAnimation("idle");
            break;
        case RUNNING:
            this->setCurrentSpriteAnimation("running");
            break;
        case FALLING:
            this->setCurrentSpriteAnimation("falling");
            break;
    }
    this->currentState = state;
}

CreatureState Creature::getCurrentState() const
{
    return this->currentState;
}

void Creature::setCollisionBox(CollisionBox collisionBox)
{
    this->collisionBox = collisionBox;
    this->collisionBox.init(ResourceManager::getShader("primitive"));
}
