//
// Created by Maciej on 25/07/2024.
//

#include <iostream>
#include "World.h"



World::World(sf::Vector2u l_windowSize) {
        m_blockSize = 16;

        m_windowSize = l_windowSize;
        m_apple.setFillColor(sf::Color::Red);
        m_apple.setRadius(m_blockSize / 2);

        for (int i=0; i < 4; i++) {
            m_bounds[i].setFillColor(sf::Color(255,255,0));
            if (!((i + 1) % 2)) {
                m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
            } else {
                m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
            }
            if (i < 2) {
                m_bounds[i].setPosition(0,0);
            } else {
                m_bounds[i].setOrigin(m_bounds[i].getSize());
                m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
            }
        }
}

World::~World() {

}

int World::getBlockSize() {
    return m_blockSize;
}

void World::respawnApple() {
    std::cout << "respawn \n";
    int maxX = (m_windowSize.x / m_blockSize) - 2;
    int maxY = (m_windowSize.y / m_blockSize) - 2;

    m_item = sf::Vector2i(
            rand() % maxX + 1,
            rand() % maxY + 1
            );
    m_apple.setPosition(
            m_item.x * m_blockSize,
            m_item.y * m_blockSize
            );
}

void World::update(Snake &l_snake) {
    if (l_snake.getPosition() == m_item) {
        std::cout << "zjadl \n";
        l_snake.extend();
        l_snake.ateApple = true;
        respawnApple();
    }

    int gridSizeX = m_windowSize.x / m_blockSize;
    int gridSizeY = m_windowSize.y / m_blockSize;

    if (l_snake.getPosition().x <= 0 ||
        l_snake.getPosition().x >= gridSizeX - 1 ||
        l_snake.getPosition().y <= 0 ||
        l_snake.getPosition().y >= gridSizeY - 1) {
        l_snake.lose();
    }
}

void World::render(sf::RenderWindow &l_window) {
    for (int i = 0; i<4; i++) {
        l_window.draw(m_bounds[i]);
    }

    l_window.draw(m_apple);
}

sf::Vector2f World::getApplePosition() {
    return m_apple.getPosition();
}

sf::Vector2u World::getWindowSize() {
    return m_windowSize;
}
