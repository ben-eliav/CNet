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
    vector<Matrix> outputs;
    double lr;
    size_t sample_size;
public:
    NeuralNetwork(vector<int> layer_sizes, double lr, size_t sample_size);
    Matrix forward(Matrix *x);
    void backpropagate(const Matrix &input, int label, const Matrix &output);
};

#endif //NEURALNETWORK_NEURALNETWORK_H
