#include "../include/Neuron.h"

Neuron::Neuron(int numOfOutputs, int index) {
    for (int i = 0; i < numOfOutputs; i++) {
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

    for (int i = 0; i < prevLayer.size(); i++)
        sum += prevLayer[i].getOutputValue() * prevLayer[i].outputWeights[0][myIndex];

    outputValue = Neuron::transferFunction(sum);
}

void Neuron::dualFeedForward(Layer &prevLayer0, Layer &prevLayer1) {
    double sum = 0.0;

    for (int i = 0; i < prevLayer0.size(); i++)
        sum += prevLayer0[i].getOutputValue() * prevLayer0[i].outputWeights[1][myIndex];

    for (int i = 0; i < prevLayer1.size(); i++)
        sum += prevLayer1[i].getOutputValue() * prevLayer1[i].outputWeights[1][myIndex];

    if (myIndex == 3)
        outputValue = Neuron::transferFunction2(sum);
    else
        outputValue = Neuron::transferFunction(sum);
}

double Neuron::transferFunction(double x) {
    return tanh(x); // Returns a value in [-1.0, 1.0]
    
    // tanh(x) derivative approximation = 1.0 - x * x (for further reference) 
}

double Neuron::transferFunction2(double x) {
    return mapInteger(x, -255.0, 255.0, -1.0, 1.0);
}