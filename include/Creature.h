#include "../include/NeuralNet.h"

class Creature {
    public:
        Creature(int argx, int argy, int argsize);
        int getXPos();
        int getYPos();
        int getSize();
        void Update();

    private:
        NeuralNet *neuralNet;
        int x, y;
        int size;
};