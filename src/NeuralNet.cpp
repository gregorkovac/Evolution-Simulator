#include "../include/NeuralNet.h"

NeuralNet::NeuralNet(vector<int> &topology) {
    int numberOfLayers = topology.size();

    // Generates layers 
    for (int i = 0; i < numberOfLayers; i++) {
        layers.push_back(Layer());

        // Generates neurons in layer (+ 1 extra bias neuron)
        for (int j = 0; j <= topology[i]; j++) {
            layers.back().push_back(Neuron());
            printf("Added neuron!\n");
        }
    }
}

void NeuralNet::feedForward(vector<double> &inputValues) {

}

void NeuralNet::getResults(vector<double> &resultValues) {
    
}