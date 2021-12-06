#ifndef NEURALNET_H
#define NEURALNET_H

#include <vector>
#include <assert.h>
#include "../include/Neuron.h"

using namespace std;

class NeuralNet {
    public:
        NeuralNet(vector<int> &topology); // Class constructor. Accepts topology in the form of "(3, 2, 1)" (number of neurons per layer)
        void feedForward(vector<double> &inputValues); // Feeds input values to the neural net
        void getResults(vector<double> &resultValues); // Gets output from the neural net
    private:
        vector<Layer> layers;
};

#endif