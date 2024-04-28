//
// Created by Ben on 28/04/2024.
//

#include "neuralnetwork.h"
#include <iostream>

using namespace std;

NeuralNetwork::NeuralNetwork(vector<int> layer_sizes, double lr, size_t sample_size) : lr(lr), sample_size(sample_size) {
    for (int i = 0; i < layer_sizes.size() - 1; i++) {
        weights.push_back(random_init(layer_sizes[i+1], layer_sizes[i]));
        biases.push_back(random_init(layer_sizes[i + 1], 1));
    }
}

// Assuming the input is a single example
Matrix NeuralNetwork::forward(Matrix *x) {
    if (x->shape.second != 1) {
        throw MatrixException("Input must be a single example");
    }
    for (int i = 0; i < weights.size()-1; i++) {
        outputs.push_back(weights[i] * (*x) + biases[i]);
        hidden.push_back(sigmoid(outputs.back()));
        x = &hidden.back();

    }
    Matrix final_out = weights.back() * (*x) + biases.back();
    final_out = softmax(final_out);
    return final_out;
}

void NeuralNetwork::backpropagate(const Matrix &input, int label, const Matrix &output) {
    Matrix y_true = one_hot(label, output.shape.first);
    Matrix error = output - y_true;

    for (int i = weights.size()-1; i >= 0; i--) {
        if (i > 0) {
            Matrix d_weights = error * hidden[i-1].transpose();
            Matrix d_biases = error;
            error = weights[i].transpose() * d_biases;
            error = d_sigmoid(outputs[i-1]) * error;
            weights[i] = weights[i] - d_weights * lr;
            biases[i] = biases[i] - d_biases * lr;
        }
        else {
            Matrix d_weights = error * input.transpose();
            Matrix d_biases = error;
            weights[i] = weights[i] - d_weights * lr / sample_size;
            biases[i] = biases[i] - d_biases * lr / sample_size;
        }
    }
}
