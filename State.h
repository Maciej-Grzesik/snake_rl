//
// Created by Maciej on 25/07/2024.
//

#ifndef MOUNTAINCAR_STATE_H
#define MOUNTAINCAR_STATE_H

#include <tuple>
#include "SFML/System/Vector2.hpp"

struct State {
    sf::Vector2i snakeHead;
    sf::Vector2f applePosition;
    bool wallUp, wallDown, wallLeft, wallRight;

    bool operator<(const State& other) const {
        return std::tie(snakeHead.x ,snakeHead.y, applePosition.x, applePosition.y, wallUp, wallDown, wallLeft, wallRight) <
               std::tie(other.snakeHead.x, other.snakeHead.y, other.applePosition.x, other.applePosition.y, other.wallUp, other.wallDown, other.wallLeft, other.wallRight);
    }
};



#endif //MOUNTAINCAR_STATE_H
