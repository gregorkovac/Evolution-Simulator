#include "../include/Creature.h"

Creature::Creature(int argx, int argy, int argsize) {
    vector<int> topology;
    vector<int> dna;

    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);

    dna.push_back(6639); // 0001100111101111

    neuralNet = new NeuralNet(topology, dna);

    x = argx;
    y = argy;
    size = argsize;
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

void Creature::Update() {
    
}