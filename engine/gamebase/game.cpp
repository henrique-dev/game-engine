#include "game.h"
#include "resource_manager.h"
#include "spriterenderer.h"
#include "sprite.h"
#include <iostream>
#include <vector>
#include "spriteutils.h"
#include "creature.h"
#include "tile.h"
#include "camera2d.h"

// Game-related State data
std::vector<Sprite*>* sprites;
std::vector<Creature*>* creatures;
std::vector<Tile*>* tiles;
Camera2D* camera;

const int mapaWidth = 36;
const int mapaHeigth = 17;
int mapa[mapaHeigth][mapaWidth] = { 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 1,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 1,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 1, 0, 3, 1 ,1, 2, 0, 0, 0, 0, 0, 0, 1 ,0, 0, 0, 0, 0, 1,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 ,0, 0, 0, 0, 1, 0, 0, 5, 0 ,0, 5, 0, 0, 0, 0, 0, 1, 1 ,1, 1, 0, 0, 1, 1,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 1, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 1, 1, 1 ,0, 1, 0, 0, 0, 1,
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 1, 1, 1, 1 ,0, 1, 0, 0, 0, 1,
										0, 0, 0, 0, 0, 0, 0, 3, 2, 0, 0, 0 ,0, 1, 1, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 1, 1, 1, 1, 1 ,0, 1, 1, 0, 0, 1,
										1, 1, 1, 1, 1, 1, 1, 4, 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 ,1, 1, 1, 1, 1, 1, 1, 1, 1 ,0, 1, 0, 0, 0, 1,
										0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 1, 0, 0, 0, 1,
										0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 1, 0, 0, 1, 1,
										0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 1, 0, 0, 0, 1,
										0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 1, 0, 0, 0, 1,
										0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 1, 1, 0, 0, 1,
										0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 1,
										0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 1, 1,
										0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 1,
										0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, };

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), width(width), height(height)
{

}

Game::~Game()
{
	//delete sprites;
}

void Game::init()
{	
	loadShaders();
	loadTextures();	
	loadObjects();
}

void Game::loadShaders()
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
}

void Game::loadTextures()
{
	// Load textures
	ResourceManager::loadTexture("textures/woman_run_cicles.png", GL_TRUE, "running");
	ResourceManager::loadTexture("textures/woman_run_arms_cicles.png", GL_TRUE, "running-arm");
	ResourceManager::loadTexture("textures/woman_character_idle.png", GL_TRUE, "idle");
	ResourceManager::loadTexture("textures/woman_character_jump.png", GL_TRUE, "jumping");
	ResourceManager::loadTexture("textures/woman_character_fall.png", GL_TRUE, "falling");
	ResourceManager::loadTexture("textures/tiles.png", GL_TRUE, "tiles");
}

void Game::loadObjects()
{
	// Set render-specific controls
	creatures = new std::vector<Creature*>;	

	Creature* creature = new Creature(300, -400, 300, 300, "idle");

	std::map<std::string, CollisionBox> colls = CollisionBox::generateBorderCollision(glm::vec2(0, -400), glm::vec2(75, 190), 10);
	creature->setCollisionBox(colls);

	creature->setCollisionBox(CollisionBox(0, 0, 150, 150), "base");

	camera = new Camera2D(0, 0, 0, 0, 0, 0, ResourceManager::getShader("sprite"));
	camera->setTarget(creature);

	SpriteAnimation * sa;

	sa = new SpriteAnimation(
		SpriteUtils::generateSpriteFromTexture(ResourceManager::getShader("sprite"), ResourceManager::getTexture("running"), 1, 10, 0, 10),
		SpriteUtils::generateSpriteFromTexture(ResourceManager::getShader("sprite"), ResourceManager::getTexture("running-arm"), 1, 10, 0, 10), 4);
	creature->setSpritesAnimation("running", sa);

	sa = new SpriteAnimation(SpriteUtils::generateSpriteFromTexture(ResourceManager::getShader("sprite"), ResourceManager::getTexture("idle"), 1, 3, 0, 3), 10);
	creature->setSpritesAnimation("idle", sa);

	sa = new SpriteAnimation(SpriteUtils::generateSpriteFromTexture(ResourceManager::getShader("sprite"), ResourceManager::getTexture("jumping"), 1, 1, 0, 1), 1);
	creature->setSpritesAnimation("jumping", sa);

	sa = new SpriteAnimation(SpriteUtils::generateSpriteFromTexture(ResourceManager::getShader("sprite"), ResourceManager::getTexture("falling"), 1, 1, 0, 1), 1);
	creature->setSpritesAnimation("falling", sa);

	creatures->push_back(creature);

	SpriteAnimation* stile = new SpriteAnimation(SpriteUtils::generateSpriteFromTexture(ResourceManager::getShader("sprite"), ResourceManager::getTexture("tiles"), 1, 1, 0, 1), 10);

	tiles = new std::vector<Tile*>;
	for (int i = 0; i < mapaHeigth; i++)
	{
		for (int j = 0; j < mapaWidth; j++)
		{
			if (mapa[i][j] != 0)
			{
				Tile* tile = new Tile(j * 100, i * 100, 100, 100, "tiles1");
				//tile->setCollisionBox(CollisionBox(0, 0, 100, 100));
				tile->setCollisionBox(CollisionBox(0, 0, 100, 100));
				tile->setSpritesAnimation("tiles1", stile);
				tiles->push_back(tile);
			}
		}
	}
}

bool teste = false;

void Game::update(GLfloat dt, GLfloat t)
{
	for (Creature* c : *creatures)
	{
		bool canFall = true;
		for (Tile* tile : *tiles)
		{

		}
		if (c->getCurrentState() != JUMPING && c->getCurrentState() != FALLING && canFall)
		{
			c->setCurrentState(FALLING);
			c->move(0, 0);
			c->jump(glfwGetTime(), 0);
		}
		c->update(dt, t);
	}

	for (Tile* tile : *tiles)
	{
		tile->update(dt, t);
	}

	camera->update();
}


void Game::processInput(GLfloat dt)
{
	if ((int)this->Keys[GLFW_KEY_D][0] == GLFW_PRESS || (int)this->Keys[GLFW_KEY_D][0] == GLFW_REPEAT)
	{
		for (Creature* c : *creatures)
		{
			c->move(5, 0);
			//camera->move(-5, 0);
			if (c->getCurrentState() != JUMPING && c->getCurrentState() != FALLING) c->setCurrentState(RUNNING);
		}
	}
	else if ((int)this->Keys[GLFW_KEY_A][0] == GLFW_PRESS || (int)this->Keys[GLFW_KEY_A][0] == GLFW_REPEAT)
	{
		for (Creature* c : *creatures)
		{
			c->move(-5, 0);
			//camera->move(5, 0);
			if (c->getCurrentState() != JUMPING && c->getCurrentState() != FALLING) c->setCurrentState(RUNNING);
		}
	}
	else if ((int)this->Keys[GLFW_KEY_SPACE][0] == GLFW_RELEASE)
	{
		for (Creature* c : *creatures)
		{
			if (c->getCurrentState() != JUMPING && c->getCurrentState() != FALLING) c->setCurrentState(IDLE);
		}
	}
	if ((int)this->Keys[GLFW_KEY_SPACE][0] == GLFW_PRESS)
	{
		for (Creature* c : *creatures)
		{
			if ((c->getCurrentState() == IDLE || c->getCurrentState() == RUNNING) && c->getCurrentState() != JUMPING)
			{
				c->jump(glfwGetTime(), -70);
				c->move(0, 20);
				c->setCurrentState(JUMPING);
			}
		}
	}
}

void Game::render()
{
	//sprites->at(contador/5)->draw(0, 0, 800, 600, 0.0f, 1.0f, 1.0f, 1.0f);
	for (Creature* c : *creatures)
	{
		c->draw();
	}

	for (Tile* t : *tiles)
	{
		t->draw();
	}
}

bool checkCollision(CollisionBox box1, CollisionBox box2)
{
	bool collisionX = box1.getPos().x + box1.getSize().x >= box2.getPos().x
		&& box2.getPos().x + box2.getSize().x >= box1.getPos().x;
	bool collisionY = box1.getPos().y + box1.getSize().y >= box2.getPos().y
		&& box2.getPos().y + box2.getSize().y >= box1.getPos().x;
	return collisionX && collisionY;
}
