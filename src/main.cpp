#include <stdio.h>
#include <random>
#include "../include/SimulationHandler.h"
#include "../include/Misc.h"

#define TICK_INTERVAL 5

static Uint32 next_time;

Uint32 time_left(void)
{
    Uint32 now;

    now = SDL_GetTicks();
    if(next_time <= now)
        return 0;
    else
        return next_time - now;
}

SimulationHandler *simulationHandler = nullptr;

int main(int argc, char* argv[]) {

    srand(time(NULL));

    simulationHandler = new SimulationHandler();

    simulationHandler->init("Evolution simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, 100);

    next_time = SDL_GetTicks() + TICK_INTERVAL;

    while (simulationHandler->isRunning()) {
        simulationHandler->handleEvents();
        simulationHandler->update();
        simulationHandler->render();

        SDL_Delay(time_left());
        next_time += TICK_INTERVAL;
    }

    simulationHandler->clean();

    return 0;
}