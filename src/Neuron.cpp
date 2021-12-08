#include "../include/Neuron.h"

Neuron::Neuron(int numOfOutputs, int index) {
    for (int i = 0; i < numOfOutputs; i++) {
        //outputWeights.push_back(randomWeight());
        outputWeights[0].push_back(0.0);
        outputWeights[1].push_back(0.0);
    }

    myIndex = index;
}

double Neuron::randomWeight() {
    return rand() / double(RAND_MAX);
}

void Neuron::setOutputValue(double value) {
    outputValue = value;
}

double Neuron::getOutputValue() {
    return outputValue;
}

void Neuron::feedForward(Layer &prevLayer) {
    double sum = 0.0;

    for (int i = 0; i < prevLayer.size(); i++) {
        sum += prevLayer[i].getOutputValue() * prevLayer[i].outputWeights[0][myIndex];
    }

    outputValue = Neuron::transferFunction(sum);
}

double Neuron::transferFunction(double x) {
    return tanh(x); // Returns a value in [-1.0, 1.0]
    
    // tanh(x) derivative approximation = 1.0 - x * x (for further reference) 
}