#include "../include/NeuralNet.h"

class Creature {
    public:
        Creature(int argx, int argy, int argsize);
        int getXPos();
        int getYPos();
        int getSize();

    private:
        NeuralNet *neuralNet;
        int x, y;
        int size;
};