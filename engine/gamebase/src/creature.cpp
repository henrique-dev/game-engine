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

void Creature::updateCollisionBox()
{
    float x = (this->getPos().x + this->getSize().x / 2) - (this->collisionBox["base"].getSize().x / 2);
    float y = (this->getPos().y + this->getSize().y) - (this->collisionBox["base"].getSize().y);
    //this->collisionBox["base"].setX((this->getPos().x + this->getSize().x / 2) - (this->collisionBox["base"].getSize().x / 2));
    //this->collisionBox["base"].setY((this->getPos().y + this->getSize().y) - (this->collisionBox["base"].getSize().y));
    std::vector<std::string> v;
    for(std::map<std::string,CollisionBox>::iterator it = this->collisionBox.begin(); it != this->collisionBox.end(); ++it) {
      //v.push_back(it->first);
      this->collisionBox[it->first].setX(x);
      this->collisionBox[it->first].setY(y);
    }
}

void Creature::setX(float x)
{
    this->pos.x = x;
    this->updateCollisionBox();
}

void Creature::setY(float y)
{
    this->pos.y = y;
    this->updateCollisionBox();
}

void Creature::update(float dt, float t)
{
    if (this->currentState == JUMPING || this->currentState == FALLING)
    {
        //float tempo = (t - this->jumpTime) * 1.5f;
        float tempo = (t - this->jumpTime) / 50;
        this->pos += this->speed * tempo;
        this->pos.y += (this->speed.y * tempo) + (15 * (float)pow(tempo, 2)) / 2.0f;
        this->speed.y += 15 * tempo;
        this->speed.y = (this->speed.y > 12.0f) ? 12.0f : this->speed.y;
        //this->speed.y = (this->speed.y > 10.0f) ? 10.0f : this->speed.y;
        if (this->speed.y > 0)
        {
            this->setCurrentState(FALLING);
        }
    }
    this->getCurrentSpriteAnimation()->animate();

    this->updateCollisionBox();
}

void Creature::invert(bool invert)
{
    this->invertSprite = invert;
}

void Creature::draw()
{
    this->getCurrentSpriteAnimation()->draw(this->getPos().x, this->getPos().y, this->getSize().x, this->getSize().y, 0.0f, this->invertSprite, 1.0f, 1.0f, 1.0f);
    //this->collisionBox["base"].draw();
    std::vector<std::string> v;
    for(std::map<std::string,CollisionBox>::iterator it = this->collisionBox.begin(); it != this->collisionBox.end(); ++it) {
      //v.push_back(it->first);
      this->collisionBox[it->first].draw();
    }
}

void Creature::move(float x, float y)
{
    if (x < 0) this->invert(true);
    if (x > 0) this->invert(false);
    float ix = this->getPos().x;
    float iy = this->getPos().y;
    this->setX( ix + x);
    this->setY( iy + y);
    this->updateCollisionBox();
}
void Creature::jump(float time, float speed)
{
    this->currentState = JUMPING;
    this->jumpTime = time;
    this->speed = glm::vec2(0, speed);
    this->updateCollisionBox();
}

void Creature::setCurrentState(CreatureState state)
{
    switch (state)
    {
        case JUMPING:
            this->setCurrentSpriteAnimation("jumping");
            break;
        case IDLE:
            this->speed.y = 0;
            this->jumpTime = 0;
            this->setCurrentSpriteAnimation("idle");
            break;
        case RUNNING:
            this->jumpTime;
            this->speed.y = 0;
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

void Creature::setCollisionBox(CollisionBox collisionBox, std::string name)
{
    this->collisionBox[name] = collisionBox;
    this->collisionBox[name].init(ResourceManager::getShader("primitive"));
}
