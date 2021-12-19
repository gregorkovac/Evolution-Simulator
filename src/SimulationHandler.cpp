#include "../include/SimulationHandler.h"

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

    // This code is here just for testing
  /*  vector<int> topology;
    vector<int> dna;

    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);

    dna.push_back(6639); // 0001100111101111

    NeuralNet net(topology, dna); 

    net.printNet();*/

    for (int i = 0; i < numCreatures; i++) {
        creatures.push_back(new Creature(randomNumberBetween(1, width-1), randomNumberBetween(1, height-1), 10));
    }
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

}

void  SimulationHandler::render() {
    //Set the draw color of renderer to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    //Clear the renderer with the draw color
    SDL_RenderClear(renderer);

    vector<Creature*>::iterator it;
    for (it = creatures.begin(); it != creatures.end(); it++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillCircle(renderer, (*it)->getXPos(), (*it)->getYPos(), (*it)->getSize());
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