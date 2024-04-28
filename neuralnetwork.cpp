//
// Created by Ben on 28/04/2024.
//

#include "neuralnetwork.h"
#include <iostream>

using namespace std;

NeuralNetwork::NeuralNetwork(vector<int> layer_sizes, double lr) : lr(lr) {
    for (int i = 0; i < layer_sizes.size() - 1; i++) {
        weights.push_back(random_init(layer_sizes[i+1], layer_sizes[i]));
        biases.push_back(random_init(layer_sizes[i + 1], 1));
    }
}

// Assuming the input is a single example
Matrix NeuralNetwork::forward(Matrix x) {
    if (x.shape.second != 1) {
        throw MatrixException("Input must be a single example");
    }
    for (int i = 0; i < weights.size()-1; i++) {
        x = weights[i] * x + biases[i];
        x = sigmoid(x);
        hidden.push_back(x);
        gradients.push_back(d_sigmoid(x));
    }
    x = weights.back() * x + biases.back();
    x = softmax(x);
    return x;
}

// Assuming that the neural network is a classification network using softmax + cross entropy at the end. Also, the input is a single example.
// For now: assuming there are 2 layers
void NeuralNetwork::backpropagate(Matrix input, const Matrix &target, const Matrix &output) {
    Matrix d_before = output - target;
    vector<Matrix> final_gradients;
    for (int i = weights.size() - 1; i >= 0; i--) {
    }
}
