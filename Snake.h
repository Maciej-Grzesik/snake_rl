//
// Created by Maciej on 25/07/2024.
//

#ifndef MOUNTAINCAR_SNAKE_H
#define MOUNTAINCAR_SNAKE_H

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

struct SnakeSegment {
    sf::Vector2i position;
    SnakeSegment(int x, int y) : position(x,y) {}
};

enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

class Snake {
public:
    Snake(int l_size);
    ~Snake();

    void setDirection(Direction l_dir);
    Direction getDirection();
    int getSpeed();
    sf::Vector2i getPosition();

    bool hasLost();
    bool hasEatenApple();

    void lose();
    void toggleLost();

    void extend();
    void reset();

    void move();
    void tick();
    void cut(int l_segments);
    void render(sf::RenderWindow& l_window);

    bool ateApple;

private:
    void checkCollision();


    std::vector<SnakeSegment> m_body;
    int m_size;
    Direction m_dir;
    int m_speed;
    bool m_lost;
    sf::RectangleShape m_bodyRect;

};
#endif //MOUNTAINCAR_SNAKE_H
