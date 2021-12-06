#include <stdio.h>
#include <vector>
#include "../include/NeuralNet.h"

using namespace std;

int main(int argc, char* argv[]) {
    vector<int> topology;

    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(1);

    NeuralNet net(topology); 

    return 0;
}