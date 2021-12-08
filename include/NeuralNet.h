#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>
#include <assert.h>
#include "../include/Neuron.h"

using namespace std;

class NeuralNet {
    public:
        NeuralNet(vector<int> &topology, vector<int> &dna); // Class constructor. Accepts topology in the form of "(3, 2, 1)" (number of neurons per layer)
        void feedForward(vector<double> &inputValues); // Feeds input values to the neural net
        void getResults(vector<double> &resultValues); // Gets output from the neural net
        void printNet();
    private:
        vector<Layer> layers;
};

#endif

/*

xxxx xxxx xxxx xxxx
1222 2344 4455 5555


1 - source type (0 = internal, 1 = input)
2 - source id
3 - destination type (0 = internal, 1 = output)
4 - output id
5 - connection weight




*/