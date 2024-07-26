#ifndef MOUNTAINCAR_GAME_H
#define MOUNTAINCAR_GAME_H

#include <SFML/Graphics.hpp>
#include "Window.h"
#include "World.h"
#include "Snake.h"
#include "QLearningAgent.h"

class Game {
public:
    Game();
    ~Game();

    void update();
    void render();
    void handleInput();
    void restartClock();

    void move();

    sf::Time getElapsed();
    Window* getWindow();

    // Train the agent for a specified number of epochs
    void trainAgent(int epochs);

private:
    Window m_window;
    World m_world;
    Snake m_snake;
    QLearningAgent agent;

    sf::Clock m_clock;
    sf::Time m_elapsed;

    bool training;
};

#endif //MOUNTAINCAR_GAME_H
