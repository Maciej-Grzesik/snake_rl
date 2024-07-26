#include <iostream>
#include "Game.h"
#include "SFML/Window/Keyboard.hpp"

Game::Game() : m_window("Snake", sf::Vector2u(800, 600)),
               m_snake(m_world.getBlockSize()),
               m_world(sf::Vector2u(400, 300)),
               agent(&m_snake, &m_world) {
    m_world.respawnApple();
}

Game::~Game() {}

void Game::update() {
    m_window.update();
    float timestep = 1.0f / m_snake.getSpeed();
    if (m_elapsed.asSeconds() >= timestep) {
        agent.train();
        m_elapsed -= sf::seconds(timestep);
    }
}

void Game::move() {}

void Game::render() {
    m_window.beginDraw();
    m_world.render(*m_window.getRenderWindow());
    m_snake.render(*m_window.getRenderWindow());
    m_window.endDraw();
}

sf::Time Game::getElapsed() {
    return m_elapsed;
}

void Game::restartClock() {
    m_elapsed += m_clock.restart();
}

void Game::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        && m_snake.getDirection() != Direction::DOWN) {
        m_snake.setDirection(Direction::UP);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
               && m_snake.getDirection() != Direction::UP) {
        m_snake.setDirection(Direction::DOWN);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
               && m_snake.getDirection() != Direction::RIGHT) {
        m_snake.setDirection(Direction::LEFT);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
               && m_snake.getDirection() != Direction::LEFT) {
        m_snake.setDirection(Direction::RIGHT);
    }
}

Window* Game::getWindow() {
    return &m_window;
}

void Game::trainAgent(int epochs) {
    std::cout << "Training agent for " << epochs << " epochs...\n";
    for (int i = 0; i < epochs; ++i) {
        agent.train();
        if ((i+1) % 1000 == 0) { // Log progress every 1000 epochs
            std::cout << "Epoch " << i+1 << " completed.\n";
        }
    }
    std::cout << "Training completed.\n";
}
