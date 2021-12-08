#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <stdlib.h>
#include <math.h>

using namespace std;

class Neuron; // Declaration for use in typedef
typedef vector<Neuron> Layer;

class Neuron {
    public:
        Neuron(int numOfOutputs, int index);
        void setOutputValue(double value);
        double getOutputValue();
        void feedForward(Layer &prevLayer);
        vector<double> outputWeights[2];
    private:
        double randomWeight();
        static double transferFunction(double x);
        int myIndex;
        double outputValue;
};

#endif