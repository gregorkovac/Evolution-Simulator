#include <stdio.h>
#include <vector>
#include "../include/NeuralNet.h"

using namespace std;

int main(int argc, char* argv[]) {
    vector<int> topology;
    vector<int> dna;

    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);

    dna.push_back(6639); // 0001100111101111


    NeuralNet net(topology, dna); 

    net.printNet();

    return 0;
}