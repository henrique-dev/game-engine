#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
    public:
        GameState State;
        GLchar Keys[1024][1];
        int action;
        GLuint width, height;

        Game(GLuint width, GLuint height);
        ~Game();

        void Init();

        void processInput(GLfloat dt);
        void update(GLfloat dt, GLfloat t);
        void render();
};

#endif // GAME_H
