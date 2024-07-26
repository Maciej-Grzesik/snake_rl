//
// Created by Maciej on 25/07/2024.
//

#include <iostream>
#include "Snake.h"

Snake::Snake(int l_size) {
    m_size = l_size;
    m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
    reset();
}

Snake::~Snake() {

}

void Snake::reset() {
    m_body.clear();

    m_body.emplace_back(10,7);
    m_body.emplace_back(10,6);
    m_body.emplace_back(10,5);

    setDirection(Direction::NONE);
    m_speed = 15;
    m_lost = false;
    ateApple = false;
}

void Snake::setDirection(Direction l_dir) {
    m_dir = l_dir;
}

Direction Snake::getDirection() {
    return m_dir;
}

int Snake::getSpeed() {
    return m_speed;
}

sf::Vector2i Snake::getPosition() {
    return (!m_body.empty() ? m_body.front().position : sf::Vector2i(1, 1));
}

bool Snake::hasLost() {
    return m_lost;
}

void Snake::lose() {
    m_lost = true;
}

void Snake::toggleLost() {
    m_lost = !m_lost;
}

void Snake::extend() {
    if (m_body.empty()) {
        return;
    }
    SnakeSegment& tail_head = m_body[m_body.size() - 1];

    if (m_body.size() > 1) {
        SnakeSegment& tail_bone = m_body[m_body.size() - 2];
        if(tail_head.position.x == tail_bone.position.x){
            if(tail_head.position.y > tail_bone.position.y){
                m_body.push_back(SnakeSegment(
                        tail_head.position.x, tail_head.position.y + 1));
            } else {
                m_body.push_back(SnakeSegment(
                        tail_head.position.x, tail_head.position.y - 1));
            }
        } else if(tail_head.position.y == tail_bone.position.y){
            if(tail_head.position.x > tail_bone.position.x){
                m_body.push_back(SnakeSegment(
                        tail_head.position.x + 1, tail_head.position.y));
            } else {
                m_body.push_back(SnakeSegment(
                        tail_head.position.x - 1, tail_head.position.y));
            }
        }
    } else {
        if(m_dir == Direction::UP){
            m_body.push_back(SnakeSegment(
                    tail_head.position.x, tail_head.position.y + 1));
        } else if (m_dir == Direction::DOWN){
            m_body.push_back(SnakeSegment(
                    tail_head.position.x, tail_head.position.y - 1));
        } else if (m_dir == Direction::LEFT){
            m_body.push_back(SnakeSegment(
                    tail_head.position.x + 1, tail_head.position.y));
        } else if (m_dir == Direction::RIGHT){
            m_body.push_back(SnakeSegment(
                    tail_head.position.x - 1, tail_head.position.y));
        }
    }
}

void Snake::tick() {
    if (m_body.empty()) {
        return;
    }
    if (m_dir == Direction::NONE) {
        return;
    }
    move();
    checkCollision();
}

void Snake::move() {
    for (int i = m_body.size() - 1; i > 0; i--) {
        m_body[i].position = m_body[i-1].position;
    }

    if (m_dir == Direction::LEFT){
        --m_body[0].position.x;
    } else if (m_dir == Direction::RIGHT){
        ++m_body[0].position.x;
    } else if (m_dir == Direction::UP){
        --m_body[0].position.y;
    } else if (m_dir == Direction::DOWN){
        ++m_body[0].position.y;
    }
}

void Snake::checkCollision() {
    if (m_body.size() < 5) {
        return;
    }
    SnakeSegment& head = m_body.front();

    for (auto iterator = m_body.begin() + 1; iterator != m_body.end(); iterator++) {
        if (iterator->position == head.position) {
            int segments = m_body.end() - iterator;
            cut(segments);
            break;
        }
    }
}

void Snake::cut(int l_segments) {
    for (int i=0; i < l_segments; i++) {
        m_body.pop_back();
    }
    lose();
}

void Snake::render(sf::RenderWindow &l_window) {
    if (m_body.empty()) {
        return;
    }

    m_bodyRect.setFillColor(sf::Color::Green);
    for (auto & iterator : m_body) {
        m_bodyRect.setPosition(iterator.position.x * m_size, iterator.position.y * m_size);
        l_window.draw(m_bodyRect);
    }
}

bool Snake::hasEatenApple() {
    bool tmp = ateApple;
    ateApple = false;
    return tmp;
}
