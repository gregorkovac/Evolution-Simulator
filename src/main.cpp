#include <stdio.h>
#include <random>
#include "../include/SimulationHandler.h"
#include "../include/Misc.h"

SimulationHandler *simulationHandler = nullptr;

int main(int argc, char* argv[]) {

    srand(time(NULL));

    simulationHandler = new SimulationHandler();

    simulationHandler->init("Evolution simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, 50);

    while (simulationHandler->isRunning()) {
        simulationHandler->handleEvents();
        simulationHandler->update();
        simulationHandler->render();
    }

    simulationHandler->clean();

    return 0;
}