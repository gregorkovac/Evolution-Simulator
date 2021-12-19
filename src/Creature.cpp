#include "../include/Creature.h"

Creature::Creature(float argx, float argy, int argsize) {
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
    moveY(-1);
}

void Creature::moveX(int dir) {
    if (x > 20 && x < WINDOW_WIDTH - 20)
        x += dir * speed;
}

void Creature::moveY(int dir) {
    if (y > 20 && y < WINDOW_HEIGHT - 20)
        y += dir * speed;
}