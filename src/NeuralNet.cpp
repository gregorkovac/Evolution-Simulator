#include "../include/NeuralNet.h"

NeuralNet::NeuralNet(vector<int> &topology, vector<int> &dna) {
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

    // DNA decode
    int dnaLength = dna.size();
    for (int i = 0; i < dnaLength; i++) {
        short srcType, srcID, destType, destID, weight;

        srcType = (dna[i] & 32768) >> 15;
        srcID = (dna[i] & 28672) >> 12;
        destType = ((dna[i] & 2048) >> 11);
        destID = (dna[i] & 1792) >> 8;
        weight = (dna[i] & 255);

        printf("srcType: %d\n", srcType);
        printf("srcID: %d\n", srcID);
        printf("destType: %d\n", destType);
        printf("destID: %d\n", destID);
        printf("weight: %d\n", weight);

        if (srcID >= layers[srcType].size() || destID >= layers[destType].size()) {
            continue;
        }

        layers[srcType][srcID].outputWeights[destType][destID] = weight;

        /*
         x xxx x xxx xxxxxxxx
         1 222 3 444 55555555
         1 000 1 000 11111111
        
        1 - source type (0 = input, 1 = internal)
        2 - source id
        3 - destination type (0 = internal, 1 = output)
        4 - output id
        5 - connection weight
        */
    }
}

void NeuralNet::feedForward(vector<double> &inputValues) {
    assert(inputValues.size() == layers[0].size() - 1);

   // printf("rand: %f\n", inputValues[2]);

    // Assign the input values to the neurons
    for (int i = 0; i < inputValues.size(); i++) {
        layers[0][i].setOutputValue(inputValues[i]);
    }

    // Forward propagate
    /*for (int i = 1; i < layers.size(); i++) {
        Layer &prevLayer = layers[i - 1];
        for (int j = 0; j < layers[i].size() - 1; j++) {
            layers[i][j].feedForward(prevLayer);
            if (i == 2)
                layers[i][j].feedForward(layers[i - 2]);
        }
    }*/

    for (int i = 0; i < layers[1].size() - 1; i++) {
        layers[1][i].feedForward(layers[0]);
    }

    for (int i = 0; i < layers[2].size() - 1; i++) {
        layers[2][i].dualFeedForward(layers[0], layers[1]);
    }
}

void NeuralNet::getResults(vector<double> &resultValues) {
    resultValues.clear();

    for (int i = 0; i < layers.back().size() - 1; i++) {
    /*    if (layers.back()[i].getOutputValue() != 0.0)
            printf("%f\n", layers.back()[i].getOutputValue());*/

     //   switch(i) {
      //      case 3:
              //  outVal = mapInteger(outVal, -1.0, 1.0, 0.0, 5.0);
        //    break;
       // }

      //  resultValues.push_back(layers.back()[i].getOutputValue());
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
            printf("internal weights: ");    

            int numOfWeights = layers[i][j].outputWeights[0].size();
            for (int k = 0; k < numOfWeights; k++) {
                printf("%f", layers[i][j].outputWeights[0][k]);
                if (k < numOfWeights - 1)
                    printf(", ");
            }

            printf("; \n   output weights: ");   

            numOfWeights = layers[i][j].outputWeights[1].size();
            for (int k = 0; k < numOfWeights; k++) {
                printf("%f", layers[i][j].outputWeights[1][k]);
                if (k < numOfWeights - 1)
                    printf(", ");
            }

            printf(")\n");
        }
        printf("\n\n");
    }
}