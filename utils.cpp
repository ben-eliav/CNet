//
// Created by Ben on 28/04/2024.
//

#include <cmath>
#include <random>
#include "utils.h"

Matrix random_init(int rows, int cols) {
    vector<vector<double>> data;
    data.reserve(rows);
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> dist(0, 1);
    for (int i = 0; i < rows; i++) {
        vector<double> row;
        row.reserve(cols);
        for (int j = 0; j < cols; j++) {
            row.push_back(dist(gen));
        }
        data.push_back(row);
    }
    return Matrix(data);
}

Matrix zeros(int rows, int cols) {
    vector<vector<double>> data;
    data.reserve(rows);
    for (int i = 0; i < rows; i++) {
        data.emplace_back(cols, 0);
    }
    return Matrix(data);
}


#pragma region operations

Matrix exp(const Matrix &m) {
    vector<vector<double>> data;
    data.reserve(m.shape.first);
    for (const vector<double> &i : m) {
        vector<double> row;
        row.reserve(m.shape.second);
        for (double j : i) {
            row.push_back(exp(j));
        }
        data.push_back(row);
    }
    return Matrix(data);
}

Matrix sigmoid(const Matrix &m) {
    if (m.shape.second != 1) {
        throw MatrixException("Sigmoid function only works on column vectors");
    }
    vector<vector<double>> data;
    data.reserve(m.shape.first);
    for (const vector<double> &j : m) {
        data.push_back({1 / (1 + exp(-j[0]))});
    }
    return Matrix(data);
}

Matrix softmax(const Matrix &m) {
    if (m.shape.second != 1) {
        throw MatrixException("Softmax function only works on column vectors");
    }

    vector<vector<double>> data;
    data.reserve(m.shape.first);
    double sum = 0;

    for (const vector<double> &j : m) {
        sum += exp(j[0]);
        data.push_back({exp(j[0])});
    }
    for (vector<double> &j : data) {
        j[0] /= sum;
    }

    return Matrix(data);
}

Matrix relu(const Matrix &m) {
    vector<vector<double>> data;
    data.reserve(m.shape.first);
    for (const vector<double> &i : m) {
        vector<double> row;
        row.reserve(m.shape.second);
        for (double j : i) {
            row.push_back(max(0.0, j));
        }
        data.push_back(row);
    }
    return Matrix(data);
}

Matrix d_sigmoid(const Matrix &m) {

}


#pragma endregion operations

