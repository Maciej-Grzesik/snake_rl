#include <iostream>
#include "Game.h"

int main() {
    Game game;

    // Train the agent off-screen for 10,000 epochs
    game.trainAgent(100'000'000);

    // After training, run the game loop
    while (!game.getWindow()->isDone()) {
        game.handleInput();
        game.update();
        game.render();
        game.restartClock();
    }

    return 0;
}
