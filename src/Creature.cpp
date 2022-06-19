#include "../include/Creature.h"

int debug_generateDna(int srcType, int srcId, int destType, int destId, int weight) {
    int out = 0;

    out |= (srcType << 15);
    out |= (srcId << 12);
    out |= (destType << 11);
    out |= (destId << 8);
    out |= weight;

    return out;
}

Creature::Creature(float argx, float argy, int argsize, Creature* parent1, Creature* parent2) {
    if (parent1 == NULL || parent2 == NULL) {
        for (int i = 0; i < 50; i++) {
        //dna.push_back(randomNumberBetween(0, 65535));
            dna.push_back(debug_generateDna(randomNumberBetween(0,1),
                randomNumberBetween(0, 8), randomNumberBetween(0, 1),
                randomNumberBetween(0, 3), randomNumberBetween(0, 255)));
        } 

        colour.r = randomNumberBetween(50, 200);
        colour.g = randomNumberBetween(50, 200);
        colour.b = randomNumberBetween(50, 200);
        oscillatorPeriod = 1.0;
    } else {
        for (int i = 0; i < 50; i++) {
            if (randomNumberBetween(0, 10) <= 5) {
                dna.push_back(parent1->getDnaAtPosition(i));
            } else {
                dna.push_back(parent2->getDnaAtPosition(i));
            }
        }

        Colour parent1Colour = parent1->getColour();
        Colour parent2Colour = parent2->getColour();

        colour.r = 0.5 * parent1Colour.r + 0.5 * parent2Colour.r;
        colour.g = 0.5 * parent1Colour.g + 0.5 * parent2Colour.g;
        colour.b = 0.5 * parent1Colour.b + 0.5 * parent2Colour.b; 
    }

    neuralNet = new NeuralNet(*Creature::netTopology, dna);

    //neuralNet->printNet();

    x = argx;
    y = argy;
    size = argsize;
    speed = 0.3;
    age = 0.0;
}

float Creature::getXPos() {
    return x;
}

float Creature::getYPos() {
    return y;
}

int Creature::getSize() {
    return size;
}

void Creature::update(float time) {
    age = age + 0.1;

    //printf("U:%f D:%f L:%f, R:%f\n", blockageU, blockageD, blockageL, blockageR);

    vector<double> inputValues;

    inputValues.push_back(oscillator(time));
    inputValues.push_back(age);
    inputValues.push_back(random());
    inputValues.push_back(blockageUp());
    inputValues.push_back(blockageDown());
    inputValues.push_back(blockageLeft());
    inputValues.push_back(blockageRight());
    inputValues.push_back(lastMoveX());
    inputValues.push_back(lastMoveY());

    neuralNet->feedForward(inputValues);

    vector<double> outputValues;

    neuralNet->getResults(outputValues);

  /*  printf("Output values:\n");
    for (int i = 0; i < outputValues.size(); i++)
        printf("%f ", outputValues[i]);
    printf("\n");*/

    if (!isnan(outputValues[0])) {
        if (outputValues[0] > 0.0) {
            moveX(1);
        } else if (outputValues[0] < 0.0) {
            moveX(-1);
        }
    }

    if (!isnan(outputValues[1])) {
        if (outputValues[1] > 0.0)
            moveY(1);
        else if (outputValues[1] < 0.0)
            moveY(-1);
    }

    //printf("MoveVector = (%f, %f)\n", outputValues[0], outputValues[1]);

    if (outputValues[2] != 0.0) {
        int rand = randomNumberBetween(0,3);
        switch(rand) {
            case 0:
                moveX(-1);
            break;
            case 1:
                moveX(1);
            break;
            case 2:
                moveY(-1);
            break;
            case 3:
                moveY(1);
            break;
        }
    }
    
    if (outputValues[3] != 0)
        oscillatorPeriod = 2*outputValues[3];

    resetBlockage();
}

void Creature::moveX(int dir) {
    if ((blockageL < size && blockageL > 0 && dir < 0) || (blockageR < size && blockageR > 0 && dir > 0))
        return;

    float mv = dir * speed;

    if ((mv < 0 && x > 20) || (mv > 0 && x < WINDOW_WIDTH - 20))
        x += mv;
}

void Creature::moveY(int dir) {
    if ((blockageD < size && blockageD > 0 && dir < 0) || (blockageU < size && blockageU > 0 && dir > 0))
        return;

    float mv = dir * speed;

    if ((mv < 0 && y > 20) || (mv > 0 && y < WINDOW_WIDTH - 20))
        y += mv;    
}

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

double Creature::oscillator(float time) {
    return sinf(oscillatorPeriod*time);
}

double Creature::random() {
    return (float)randomNumberBetween(-100, 100)/100.0;
}

double Creature::blockageUp() {
    return blockageU;
}

double Creature::blockageDown() {
    return blockageD;
}

double Creature::blockageLeft() {
    return blockageL;
}

double Creature::blockageRight() {
    return blockageR;
}

double Creature::lastMoveX() {
    return 0.0;
}

double Creature::lastMoveY() {
    return 0.0;
}

Colour Creature::getColour() {
    return colour;
}

double Creature::getAge() {
    return age;
}

bool Creature::readyToMate() {
    if (age < 50)
        return 0;
    if (randomNumberBetween(0, 100) < 50)
        return 1;
    return 0;
}

int Creature::getDnaAtPosition(int pos) {
    return dna.at(pos);
}

void Creature::setBlockage(char dir, float dist) {
    if (dir == 'U') blockageU = dist;
    else if (dir == 'D') blockageD = dist;
    else if (dir == 'L') blockageL = dist;
    else if (dir == 'R') blockageR = dist;
}

void Creature::resetBlockage() {
    blockageU = 0;
    blockageD = 0;
    blockageL = 0;
    blockageR = 0;
}