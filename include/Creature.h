#ifndef CREATURE_H
#define CREATURE_H

#include "../include/NeuralNet.h"
#include "../include/Misc.h"

class Creature {
    public:
        Creature(float argx, float argy, int argsize);
        int getXPos();
        int getYPos();
        int getSize();
        void update();
        void moveX(int dir);
        void moveY(int dir);

    private:
        NeuralNet *neuralNet;
        float x, y;
        int size;
        float speed;
};

#endif