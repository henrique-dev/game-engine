#include <game.h>
#include <resource_manager.h>
#include <spriterenderer.h>
#include <sprite.h>
#include <iostream>
#include <vector>

// Game-related State data
SpriteRenderer  *Renderer;
Sprite *sprite[10];
std::vector<Sprite*> * sprites;
int contador = 0;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // Load shaders
    ResourceManager::loadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::getShader("sprite").SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::loadTexture("textures/woman_run_cicles.png", GL_TRUE, "face");
    float width = (float)ResourceManager::getTexture("face").width;
    float height = (float)ResourceManager::getTexture("face").height;
    // Set render-specific controls
    sprites = Sprite::generateSpriteFromTexture(ResourceManager::getTexture("face"), 1, 10, 10);
}

void Game::Update(GLfloat dt)
{
    contador += 1;
    if (contador > 99) contador = 0;
}


void Game::ProcessInput(GLfloat dt)
{

}

void Game::Render()
{
    sprites->at(contador/10)->draw(0, 0, 800, 600, 0.0f, 1.0f, 1.0f, 1.0f);
}
