#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <stdlib.h>

using namespace std;

class Neuron {
    public:
        Neuron(int numOfOutputs);
    private:
        double randomWeight();
        double outputValue;
        vector<double> outputWeights;
};

#endif