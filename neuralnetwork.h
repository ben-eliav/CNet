//
// Created by Ben on 28/04/2024.
//

#ifndef NEURALNETWORK_NEURALNETWORK_H
#define NEURALNETWORK_NEURALNETWORK_H

#include "utils.h"
#include "dataframe.h"

class NeuralNetwork {
    vector<Matrix> weights;
    vector<Matrix> biases;
    vector<Matrix> hidden;
    vector<Matrix> gradients;
    double lr;
public:
    NeuralNetwork(vector<int> layer_sizes, double lr);
    Matrix forward(Matrix x);
    void backpropagate(Matrix input, const Matrix &target, const Matrix &output);
};

#endif //NEURALNETWORK_NEURALNETWORK_H
