#ifndef CREATURE_H
#define CREATURE_H

#include "../include/NeuralNet.h"
#include "../include/Misc.h"

class Creature {
    public:    
        Creature(float argx, float argy, int argsize, Creature* parent1 = NULL, Creature* parent2 = NULL);
        float getXPos();
        float getYPos();
        int getSize();
        void update(float time);
        void moveX(int dir);
        void moveY(int dir);
        Colour getColour();
        static void initializeNetTopology();
        static vector<int> *netTopology;
        double getAge();
        bool readyToMate();
        int getDnaAtPosition(int pos);

    private:
        NeuralNet *neuralNet;
        float x, y;
        int size;
        float speed;
        double age;
        float oscillatorPeriod;
        Colour colour;
        vector<int> dna;
        
        double oscillator(float time);
        double random();
        double blockageUp();
        double blockageDown();
        double blockageLeft();
        double blockageRight();
        double lastMoveX();
        double lastMoveY();
};

#endif