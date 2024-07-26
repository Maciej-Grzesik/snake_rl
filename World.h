//
// Created by Maciej on 25/07/2024.
//

#ifndef MOUNTAINCAR_WORLD_H
#define MOUNTAINCAR_WORLD_H


#include "SFML/System/Vector2.hpp"
#include "Snake.h"
#include "SFML/Graphics/CircleShape.hpp"

class World {
public:
    World(sf::Vector2u l_windowSize);
    ~World();

    int getBlockSize();

    void respawnApple();
    sf::Vector2f getApplePosition();
    sf::Vector2u getWindowSize();

    void update(Snake& l_snake);
    void render(sf::RenderWindow& l_window);

private:
    sf::Vector2u m_windowSize;
    sf::Vector2i m_item;

    int m_blockSize;

    sf::CircleShape m_apple;
    sf::RectangleShape m_bounds[4];
};


#endif //MOUNTAINCAR_WORLD_H
