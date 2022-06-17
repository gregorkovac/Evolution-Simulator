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
    //vector<int> topology; // Create a fixed topology

    /*topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);*/

   //dna.push_back(6639); // 0001100111101111
    // dna.push_back(4351); // 0000000011111111

    // dna.push_back(35071); // 1000100011111111

   // printf("Test: %d\n", debug_generateDna(1, 1, 1, 1, 1));

   /* dna.push_back(debug_generateDna(0, 2, 1, 0, 255));
    dna.push_back(debug_generateDna(0, 0, 0, 0, 255));
    dna.push_back(debug_generateDna(0, 2, 1, 1, 255));*/

   /* dna.push_back(debug_generateDna(0, 0, 1, 0, 255)); // X
    dna.push_back(debug_generateDna(0, 0, 0, 0, 255)); // Internal for Y
    dna.push_back(debug_generateDna(1, 0, 1, 1, 255)); // Y*/

    if (parent1 == NULL || parent2 == NULL) {
        for (int i = 0; i < 50; i++) {
        //dna.push_back(randomNumberBetween(0, 65535));
            dna.push_back(debug_generateDna(randomNumberBetween(0,1),
                randomNumberBetween(0, 8), randomNumberBetween(0, 1),
                randomNumberBetween(0, 3), randomNumberBetween(0, 255)));
        } 
    } else {
        for (int i = 0; i < 50; i++) {
            if (randomNumberBetween(0, 10) <= 5) {
                dna.push_back(parent1->getDnaAtPosition(i));
            } else {
                dna.push_back(parent2->getDnaAtPosition(i));
            }
        }
    }

   // dna.push_back(debug_generateDna(0, 2, 1, 0, 100));

 //   dna.push_back(debug_generateDna(0, 0, 0, 0, 255));
   // dna.push_back(debug_generateDna(1, 0, 1, 0, 255));
   // dna.push_back(debug_generateDna(0, 2, 1, 3, 255));
   // dna.push_back(debug_generateDna(0, 2, 1, 3, 255));

 //  dna.push_back(debug_generateDna(0, 2, 1, 3, 255));
  // dna.push_back(debug_generateDna(0, 0, 1, 0, 255));

    neuralNet = new NeuralNet(*Creature::netTopology, dna);

    neuralNet->printNet();

    x = argx;
    y = argy;
    size = argsize;
    speed = 0.3;
    age = 0.0;
    oscillatorPeriod = 1.0;
    colour.r = randomNumberBetween(50, 200);
    colour.g = randomNumberBetween(50, 200);
    colour.b = randomNumberBetween(50, 200);
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

  /*  printf("Input values:\n");
    for (int i = 0; i < inputValues.size(); i++)
        printf("%f ", inputValues[i]);
    printf("\n"); */

    neuralNet->feedForward(inputValues);

    vector<double> outputValues;

    neuralNet->getResults(outputValues);

  /*  printf("Output values:\n");
    for (int i = 0; i < outputValues.size(); i++)
        printf("%f ", outputValues[i]);
    printf("\n");*/

    if (outputValues[0] > 0.0)
        moveX(1);
    else if (outputValues[0] < 0.0)
        moveX(-1);
    if (outputValues[1] > 0.0)
        moveY(1);
    else if (outputValues[1] < 0.0)
        moveY(-1);

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
    
    if (outputValues[3] != 0) {
        //printf("%f\n", outputValues[3]);
        oscillatorPeriod = 2*outputValues[3];
      //  printf("%f\n", oscillatorPeriod);
    }
}

void Creature::moveX(int dir) {
   // printf("yes\n");
  //  float xMove = x + dir * speed;
  //  if (xMove > 20 && xMove < WINDOW_WIDTH - 20)
  //      x = xMove;

    if (x > 20 && x < WINDOW_WIDTH - 20)
        x += dir * speed;
}

void Creature::moveY(int dir) {
    if (y > 20 && y < WINDOW_HEIGHT - 20)
        y += dir * speed; 

    /*
    float yMove = y + dir * speed;
    if (yMove > 20 && yMove < WINDOW_HEIGHT - 20)
        y = yMove; */
        
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

double Creature::oscillator(float time) {
   // printf("%f\n", oscillatorPeriod);
    return sinf(oscillatorPeriod*time);
}

double Creature::random() {
    return (float)randomNumberBetween(-100, 100)/100.0;
}

double Creature::blockageUp() {
    return 0.0;
}

double Creature::blockageDown() {
    return 0.0;
}

double Creature::blockageLeft() {
    return 0.0;
}

double Creature::blockageRight() {
    return 0.0;
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