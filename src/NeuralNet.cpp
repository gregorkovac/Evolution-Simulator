#include "../include/NeuralNet.h"

NeuralNet::NeuralNet(vector<int> &topology) {
    int numberOfLayers = topology.size();

    // Generates layers 
    for (int i = 0; i < numberOfLayers; i++) {
        layers.push_back(Layer());

        // Number of outputs for the next layer. The last layer doesn't have any outputs
        int numberOfOutputs = (i == topology.size() - 1) ? 0 : topology[i + 1];

        // Generates neurons in layer (+ 1 extra bias neuron)
        for (int j = 0; j <= topology[i]; j++) {
            layers.back().push_back(Neuron(numberOfOutputs, j));
          //  printf("Added neuron!\n");
        }

        // Bias neuron has a constant output value of 1.0
        layers.back().back().setOutputValue(1.0);
    }
}

void NeuralNet::feedForward(vector<double> &inputValues) {
    assert(inputValues.size() == layers[0].size() - 1);

    // Assign the input values to the neurons
    for (int i = 0; i < inputValues.size(); i++) {
        layers[0][i].setOutputValue(inputValues[i]);
    }

    // Forward propagate
    for (int i = 1; i < layers.size(); i++) {
        Layer &prevLayer = layers[i - 1];
        for (int j = 0; j < layers[i].size() - 1; j++) {
            layers[i][j].feedForward(prevLayer);
        }
    }
}

void NeuralNet::getResults(vector<double> &resultValues) {
    resultValues.clear();

    for (int i = 0; i < layers.back().size() - 1; i++) {
        resultValues.push_back(layers.back()[i].getOutputValue());
    }
}

void NeuralNet::printNet() {
    int numOfLayers = layers.size();

    for (int i = 0; i < numOfLayers; i++) {
        int numOfLayers2 = layers[i].size();

        printf("Layer %d:\n", i);

        for (int j = 0; j < numOfLayers2; j++) {
            printf("%d (", j);
            
            int numOfWeights = layers[i][j].outputWeights.size();

            for (int k = 0; k < numOfWeights; k++) {
                printf("%f", layers[i][j].outputWeights[k]);
                if (k < numOfWeights - 1)
                    printf(", ");
            }
            printf("); ");
        }
        printf("\n\n");
    }
}