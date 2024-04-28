//
// Created by Ben on 28/04/2024.
//

#ifndef NEURALNETWORK_NEURALNETWORK_H
#define NEURALNETWORK_NEURALNETWORK_H

#include "utils.h"
#include "dataframe.h"

class NeuralNetwork {
    vector<Matrix> layers;
    vector<Matrix> biases;
    double lr;
public:
    NeuralNetwork(vector<int> layer_sizes, double lr);
    Matrix forward(Matrix input);
    void train(Matrix input, Matrix target, double learning_rate);
    void backpropagate(Matrix input, Matrix target, double learning_rate);
    void save(string filename);
    void load(string filename);
};

#endif //NEURALNETWORK_NEURALNETWORK_H
