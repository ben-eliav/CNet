//
// Created by Ben on 28/04/2024.
//

#include "dataframe.h"

#ifndef NEURALNETWORK_UTILS_H
#define NEURALNETWORK_UTILS_H


Matrix random_init(int rows, int cols);
Matrix zeros(int rows, int cols);
Matrix one_hot(int label, int num_labels);
Matrix diag(const vector<double> &v);
Matrix diag(const Matrix &m);

Matrix exp(const Matrix &m);
Matrix sigmoid(const Matrix &m);
Matrix softmax(const Matrix &m);
Matrix relu(const Matrix &m);
Matrix cross_entropy_loss(const Matrix &y_true, const Matrix &y_pred);

Matrix d_sigmoid(const Matrix &m);
Matrix d_relu(const Matrix &m);  // TODO: add implementation
Matrix d_cross_entropy_loss(const Matrix &y_true, const Matrix &y_pred);

Matrix read_data_csv(const string &filename);




#endif //NEURALNETWORK_UTILS_H
