#include <game.h>
#include <resource_manager.h>
#include <spriterenderer.h>
#include <sprite.h>
#include <iostream>
#include <vector>
#include <spriteutils.h>
#include <creature.h>
#include <tile.h>
#include <camera2d.h>

// Game-related State data
std::vector<Sprite*> * sprites;
std::vector<Creature*> * creatures;
std::vector<Tile*> * tiles;
Camera2D * camera;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), width(width), height(height)
{

}

Game::~Game()
{
    //delete sprites;
}

void Game::Init()
{
    // Load shaders
    ResourceManager::loadShader("shaders/primitive.vs", "shaders/primitive.frag", nullptr, "primitive");
    ResourceManager::loadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceManager::getShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::getShader("sprite").SetMatrix4("projection", projection);

    glm::mat4 projection2 = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);

    ResourceManager::getShader("primitive").Use().SetInteger("image2", 1);
    ResourceManager::getShader("primitive").SetMatrix4("projection2", projection2);

    // Load textures
    ResourceManager::loadTexture("textures/woman_run_cicles.png", GL_TRUE, "running");
    ResourceManager::loadTexture("textures/woman_run_arms_cicles.png", GL_TRUE, "running-arm");
    ResourceManager::loadTexture("textures/woman_character_idle.png", GL_TRUE, "idle");
    ResourceManager::loadTexture("textures/woman_character_jump.png", GL_TRUE, "jumping");
    ResourceManager::loadTexture("textures/woman_character_fall.png", GL_TRUE, "falling");

    ResourceManager::loadTexture("textures/tiles.png", GL_TRUE, "tiles");
    // Set render-specific controls
    creatures = new std::vector<Creature*>;

    camera = new Camera2D(0, 0, 0, 0, 0, 0, ResourceManager::getShader("sprite"));

    Shader spriteShader = ResourceManager::getShader("sprite");

    Creature * creature = new Creature(300, -400, 200, 300, "idle");
    SpriteAnimation * sa;

    sa = new SpriteAnimation(
                             SpriteUtils::generateSpriteFromTexture(spriteShader, ResourceManager::getTexture("running"), 1, 10, 0, 10),
                             SpriteUtils::generateSpriteFromTexture(spriteShader, ResourceManager::getTexture("running-arm"), 1, 10, 0, 10), 4);
    creature->setSpritesAnimation("running", sa);

    sa = new SpriteAnimation(SpriteUtils::generateSpriteFromTexture(spriteShader, ResourceManager::getTexture("idle"), 1, 3, 0, 3), 10);
    creature->setSpritesAnimation("idle", sa);

    sa = new SpriteAnimation(SpriteUtils::generateSpriteFromTexture(spriteShader, ResourceManager::getTexture("jumping"), 1, 1, 0, 1), 1);
    creature->setSpritesAnimation("jumping", sa);

    sa = new SpriteAnimation(SpriteUtils::generateSpriteFromTexture(spriteShader, ResourceManager::getTexture("falling"), 1, 1, 0, 1), 1);
    creature->setSpritesAnimation("falling", sa);

    creature->setCollisionBox(CollisionBox(0, 0, 80, 200));

    creatures->push_back(creature);

    sa = new SpriteAnimation(SpriteUtils::generateSpriteFromTexture(spriteShader, ResourceManager::getTexture("tiles"), 1, 1, 0, 1), 10);
    tiles = new std::vector<Tile*>;
    for (int i=0; i<10; i++)
    {
        Tile * tile = new Tile(i * 100, 520, 100, 100, "tiles");
        tile->setCollisionBox(CollisionBox(0, 0, 100, 100));
        tile->setSpritesAnimation("tiles", sa);
        tiles->push_back(tile);
    }
}

void Game::update(GLfloat dt, GLfloat t)
{
    for (Creature * c : *creatures)
    {
        if (c->checkGroundCollision(0, 520, 0)) {
            if (c->getCurrentState() == JUMPING || c->getCurrentState() == FALLING)
            {
                c->setCurrentState(IDLE);
            }
        }
        c->update(dt, t);
    }

    for (Tile * tile : *tiles)
    {
        tile->update(dt, t);
    }
}


void Game::processInput(GLfloat dt)
{
    if ((int)this->Keys[GLFW_KEY_D][0] == GLFW_PRESS || (int)this->Keys[GLFW_KEY_D][0] == GLFW_REPEAT)
    {
        for (Creature * c : *creatures)
        {
            c->move(5, 0);
            camera->move(-5, 0);
            if (c->getCurrentState() != JUMPING && c->getCurrentState() != FALLING) c->setCurrentState(RUNNING);
        }
    }
    else if ((int)this->Keys[GLFW_KEY_A][0] == GLFW_PRESS || (int)this->Keys[GLFW_KEY_A][0] == GLFW_REPEAT)
    {
        for (Creature * c : *creatures)
        {
            c->move(-5, 0);
            camera->move(5, 0);
            if (c->getCurrentState() != JUMPING && c->getCurrentState() != FALLING) c->setCurrentState(RUNNING);
        }
    }
    else if ((int)this->Keys[GLFW_KEY_SPACE][0] == GLFW_RELEASE)
    {
        for (Creature * c : *creatures)
        {
            if (c->getCurrentState() != JUMPING && c->getCurrentState() != FALLING) c->setCurrentState(IDLE);
        }
    }
    if ((int)this->Keys[GLFW_KEY_SPACE][0] == GLFW_PRESS)
    {
        for (Creature * c : *creatures)
        {
            if (c->getCurrentState() != JUMPING)
            {
                c->jump(glfwGetTime(), -50);
                c->setCurrentState(JUMPING);
            }
        }
    }
}

void Game::render()
{
    //sprites->at(contador/5)->draw(0, 0, 800, 600, 0.0f, 1.0f, 1.0f, 1.0f);
    for (Creature * c : *creatures)
    {
        c->draw();
    }

    for (Tile * t : *tiles)
    {
        t->draw();
    }
}
