#include "../include/Neuron.h"

Neuron::Neuron(int numOfOutputs) {
    for (int i = 0; i < numOfOutputs; i++) {
        outputWeights.push_back(randomWeight());
    }
}

double Neuron::randomWeight() {
    return rand() / double(RAND_MAX);
}