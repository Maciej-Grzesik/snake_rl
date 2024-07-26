#ifndef MOUNTAINCAR_QLEARNINGAGENT_H
#define MOUNTAINCAR_QLEARNINGAGENT_H

#include <map>
#include "State.h"
#include "Snake.h"
#include "World.h"

class QLearningAgent {
public:
    QLearningAgent(Snake* l_snake, World* l_world);
    ~QLearningAgent();

    float getReward();
    State getCurrentState();
    Direction epsilonGreedyPolicy(State state);
    float getMaxQ(State state);

    void train();

private:
    std::map<std::pair<State, Direction>, float> m_qTable;
    float m_lr;
    float m_discount;
    float m_epsilon;
    float m_epsilonDecay;
    float m_epsilonMin;

    Snake* m_snake;
    World* m_world;
};

#endif //MOUNTAINCAR_QLEARNINGAGENT_H
