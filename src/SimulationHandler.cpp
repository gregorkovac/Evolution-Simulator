#include "../include/SimulationHandler.h"
#include <time.h>

SimulationHandler::SimulationHandler() {

}

void SimulationHandler::init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags, int numCreatures) {
    //Initialize all the systems of SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create a window
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

    //Create a renderer for the window
    renderer = SDL_CreateRenderer(window, -1, 0);

    // The simulation is now running
    running = true;

    // Initialize the creature's neural net topology
    Creature::initializeNetTopology();

    // Create creatures
    for (int i = 0; i < numCreatures; i++) {
        creatures.push_back(new Creature(randomNumberBetween(1, width-1), randomNumberBetween(1, height-1), 5));
    }

    deathFactor = 100000;
    creatureTriggerDistance = 1.0;

    tStart = clock();
}

void SimulationHandler::handleEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT){
            running = false;
        }
        if (e.type == SDL_KEYDOWN){
            running = false;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN){
            running = false;
        }
    }
}

void SimulationHandler::update() {
    float time = (double)(clock() - tStart)/CLOCKS_PER_SEC;
    int numCreatures = creatures.size();

    for (int i = 0; i < numCreatures; i++) {
        for (int j = 0; j < i; j++) {
            float ix, iy, jx, jy;
            ix = creatures[i]->getXPos();
            iy = creatures[i]->getYPos();
            jx = creatures[j]->getXPos();
            jy = creatures[j]->getYPos();

            if (i != j && euclideanDistance(ix, iy, jx, jy) <= creatureTriggerDistance) {
                float dist = abs(jx - ix);
                if (ix < jx) {
                    creatures[i]->setBlockage('R', dist);
                    creatures[j]->setBlockage('L', dist);
                } else {
                    creatures[i]->setBlockage('L', dist);
                    creatures[j]->setBlockage('R', dist);
                }

                dist = abs(jy - iy);

                if (iy < jy) {
                    creatures[i]->setBlockage('U', dist);
                    creatures[j]->setBlockage('D', dist);
                } else {
                    creatures[i]->setBlockage('D', dist);
                    creatures[j]->setBlockage('U', dist);
                }

                // Mate two creatures
                if (creatures[i]->readyToMate() && creatures[j]->readyToMate() && creatures.size() < 200) {
                    creatures.push_back(new Creature((ix + jx)/2, (iy + jy)/2, 5));
                }
            }
        }
    }

    for (int i = 0; i < numCreatures; i++) {
        // Update the creatures
        creatures[i]->update(time);

        // Remove the creature if it dies of old age or enters the kill zone
        if (randomNumberBetween(0, deathFactor) < creatures[i]->getAge() || euclideanDistance(creatures[i]->getXPos(), creatures[i]->getYPos(), WINDOW_WIDTH, WINDOW_HEIGHT) < 100) {
            creatures.erase(creatures.begin() + i);
            numCreatures--;
            i--;
            continue;
        }
    }
}

void  SimulationHandler::render() {
    //Set the draw color of renderer to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    //Clear the renderer with the draw color
    SDL_RenderClear(renderer);

    // Draw the kill zone
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawCircle(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, 100);

    // Draw the creatures
    int numCreatures = creatures.size();
    vector<Creature*>::iterator it;
    for (int i = 0; i < numCreatures; i++) {
        Colour c = creatures[i]->getColour();
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
        SDL_RenderFillCircle(renderer, creatures[i]->getXPos(), creatures[i]->getYPos(), creatures[i]->getSize());
    }

    //Update the renderer which will show the renderer cleared by the draw color which is green
    SDL_RenderPresent(renderer);
}

void  SimulationHandler::clean() {
    //Destroy the renderer created above
    SDL_DestroyRenderer(renderer);

    //Destroy the window created above
    SDL_DestroyWindow(window);

    //Close all the systems of SDL initialized at the top
    SDL_Quit();
}

bool SimulationHandler::isRunning() {
    return running;
}