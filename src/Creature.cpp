#include "../include/Creature.h"

Creature::Creature(float argx, float argy, int argsize) {
    //vector<int> topology; // Create a fixed topology
    vector<int> dna;

    /*topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);*/

    dna.push_back(6639); // 0001100111101111

    neuralNet = new NeuralNet(*Creature::netTopology, dna);

    x = argx;
    y = argy;
    size = argsize;
    speed = 0.5;
}

int Creature::getXPos() {
    return x;
}

int Creature::getYPos() {
    return y;
}

int Creature::getSize() {
    return size;
}

void Creature::update() {
    
}

void Creature::moveX(int dir) {
    if (x > 20 && x < WINDOW_WIDTH - 20)
        x += dir * speed;
}

void Creature::moveY(int dir) {
    if (y > 20 && y < WINDOW_HEIGHT - 20)
        y += dir * speed;
}

//Creature::netTopology = new vector<int>();

vector<int>* Creature::netTopology = nullptr;

void Creature::initializeNetTopology() {
    /*
        INPUTS:
            0 = Oscillator
            1 = Age
            2 = Random
            3 = Blockage Up
            4 = Blockage Down
            5 = Blockage Left
            6 = Blockage Right
            7 = Last Move X
            8 = Last Move Y
            9 = ...
        
        INTERNAL:
            0, 1, 2

        OUTPUTS:
            0 = MoveX
            1 = MoveY
            2 = MoveRandom
            3 = SetOscillatorPeriod
            4 = ...
    */

    Creature::netTopology = new vector<int>();
    Creature::netTopology->push_back(9);
    Creature::netTopology->push_back(3);
    Creature::netTopology->push_back(4);
   
}