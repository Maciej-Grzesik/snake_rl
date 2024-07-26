#include <limits>
#include <iostream>
#include <random>
#include "QLearningAgent.h"

QLearningAgent::QLearningAgent(Snake* l_snake, World* l_world)
        : m_lr(0.1),
          m_discount(0.95f),
          m_epsilon(1.f),
          m_epsilonDecay(0.995f),
          m_epsilonMin(0.01f),
          m_snake(l_snake),
          m_world(l_world) {
}

QLearningAgent::~QLearningAgent() {}

void QLearningAgent::train() {
    State currentState = getCurrentState();
    Direction action = epsilonGreedyPolicy(currentState);

    m_snake->setDirection(action);
    m_snake->tick();
    m_world->update(*m_snake);

    State nextState = getCurrentState();
    float reward = getReward();

    // Update Q-value using the Bellman equation
    float oldQValue = m_qTable[std::make_pair(currentState, action)];
    float bestFutureQ = getMaxQ(nextState);
    float newQValue = (1 - m_lr) * oldQValue + m_lr * (reward + m_discount * bestFutureQ);

    m_qTable[std::make_pair(currentState, action)] = newQValue;

    if (m_snake->hasLost()) {
        m_snake->reset();
        m_epsilon = std::max(m_epsilonMin, m_epsilon * m_epsilonDecay);
    }
}

float QLearningAgent::getReward() {
    if (m_snake->hasLost()) {
        return -100.f;
    } else if (m_snake->hasEatenApple()) {
        return 100.f;
    } else {
        return -1.f; // Minor penalty for each step
    }
}

State QLearningAgent::getCurrentState() {
    State state;
    state.snakeHead = m_snake->getPosition();
    state.applePosition = m_world->getApplePosition();

    int gridSizeX = m_world->getWindowSize().x / m_world->getBlockSize();
    int gridSizeY = m_world->getWindowSize().y / m_world->getBlockSize();

    state.wallUp = (state.snakeHead.y == 0);
    state.wallDown = (state.snakeHead.y == gridSizeY - 1);
    state.wallLeft = (state.snakeHead.x == 0);
    state.wallRight = (state.snakeHead.x == gridSizeX - 1);

    return state;
}

Direction QLearningAgent::epsilonGreedyPolicy(State state) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    if (dis(gen) < m_epsilon) {
        int random_action = rand() % 4 + 1;
        return static_cast<Direction>(random_action);
    } else {
        float bestQ = -std::numeric_limits<float>::infinity();
        Direction bestAction = Direction::DOWN;

        for (int i = 1; i < 5; i++) {
            Direction action = static_cast<Direction>(i);
            float qValue = m_qTable[std::make_pair(state, action)];
            if (qValue > bestQ) {
                bestQ = qValue;
                bestAction = action;
            }
        }
        return bestAction;
    }
}

float QLearningAgent::getMaxQ(State state) {
    float maxQ = -std::numeric_limits<float>::infinity();

    for (int i = 1; i < 5; i++) {
        Direction action = static_cast<Direction>(i);
        float qValue = m_qTable[std::make_pair(state, action)];
        if (qValue > maxQ) {
            maxQ = qValue;
        }
    }
    return maxQ;
}
