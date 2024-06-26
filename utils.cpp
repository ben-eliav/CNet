//
// Created by Ben on 28/04/2024.
//

#include <cmath>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "utils.h"

using namespace std;

#pragma region creation

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
    cout << Matrix(data) << endl;
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

Matrix one_hot(int label, size_t num_labels) {
    vector<double> data(num_labels, 0);
    data[label] = 1;
    return Matrix(data);
}

Matrix diag(const vector<double> &v) {
    vector<vector<double>> data;
    data.reserve(v.size());
    for (int i = 0; i < v.size(); i++) {
        data.emplace_back(v.size(), 0);
        data[i][i] = v[i];
    }
    return Matrix(data);
}

Matrix diag(const Matrix &m) {
    if (m.shape.first != 1 && m.shape.second != 1) {
        throw MatrixException("Diag function only works on vectors");
    }
    vector<vector<double>> data;
    data.reserve(m.shape.first);
    for (int i = 0; i < m.shape.first; i++) {
        data.emplace_back(m.shape.first, 0);
        data[i][i] = m[i][0];
    }
    return Matrix(data);
}

#pragma endregion creation

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
        throw MatrixException("Sigmoid function only works on row vectors");
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
        throw MatrixException("Softmax function only works on row vectors");
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
    Matrix sig = sigmoid(m);
    return diag(sig - sig.times(sig));
}

double cross_entropy_loss(const Matrix &y_true, const Matrix &y_pred) {
    if (y_true.shape != y_pred.shape) {
        throw MatrixException("Shapes of y_true and y_pred must be the same");
    }
    double loss = 0;
    for (int i = 0; i < y_true.shape.first; i++) {
        loss += y_true[i][0] * log(y_pred[i][0]);
    }
    return -loss;
}

double cross_entropy_loss(int y_true, const Matrix &y_pred) {
    if (y_true < 0 || y_true >= y_pred.shape.first) {
        throw MatrixException("y_true must be a valid index for y_pred");
    }
    return -log(y_pred[y_true][0]);
}


#pragma endregion operations


pair<Matrix, Matrix> read_data_csv(const string &filename, const string &label_column) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw MatrixException("Could not open file");
    }

    map<string, vector<double>> data;
    string line;
    getline(file, line);

    vector<string> headers;
    stringstream ss(line);
    string cell;

    while (getline(ss, cell, ',')) {
        cell.erase(remove_if(cell.begin(), cell.end(), [](char c) { return !isalnum(c); }), cell.end());
        headers.push_back(cell);
    }
    while (getline(file, line)) {
        int i = 0;
        ss = stringstream(line);
        while (getline(ss, cell, ',')) {
            data[headers[i++]].push_back(stod(cell));
        }
    }

    vector<vector<double>> X_data;
    vector<double> y_data;

    for (const string &header : headers) {
        if (header == label_column) {
            y_data = data[header];
        } else {
            X_data.push_back(data[header]);
        }
    }


    return pair<Matrix, Matrix>{Matrix(X_data), Matrix(y_data)};
}