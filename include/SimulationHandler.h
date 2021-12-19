#ifndef SIMULATIONHANDLER_H
#define SIMULATIONHANDLER_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <vector>
#include <random>
#include "../include/NeuralNet.h"
#include "../include/Creature.h"
#include "../include/Misc.h"

using namespace std;

class SimulationHandler {
    public:
        SimulationHandler();
        void init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags, int numCreatures); // Initializes the simulation
        void handleEvents(); // Handles events, such as key presses
        void update(); // Updates all game objects
        void render(); // Renders graphics
        void clean(); // Cleans up after finishing
        bool isRunning(); // Returns true if the simulation is running

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool running;
        vector<Creature*> creatures; 
};

#endif