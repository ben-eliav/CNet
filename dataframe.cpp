//
// Created by Ben on 28/04/2024.
//

#include "dataframe.h"
#include <iostream>
#include <cmath>

using namespace std;

void print_vector(const vector<double> &vec) {
    for (double i : vec) {
        cout << i << " ";
    }
    cout << endl;
}

#pragma region Exceptions


MatrixException::MatrixException(char const *msg) : message(msg){}

char *MatrixException::what() {
    return const_cast<char *>(message);
}

inline vector<vector<double>> vec2mat(const vector<double> &vec, bool row = false) {
    // convert a vector to a column vector matrix
    vector<vector<double>> result;
    if (row) {
        result.push_back(vec);
        return result;
    }
    result.reserve(vec.size());
    for (double i : vec) {
        result.push_back({i});
    }
    return result;
}

#pragma endregion Exceptions

Matrix::Matrix(vector<vector<double>> data) : data{move(data)} {
    try {
        shape.first = this->data.size();
        shape.second = this->data[0].size();
        if (!shape.second) {
            throw MatrixException("Cannot create a matrix with size 0");
        }
    }
    catch (exception &e) {
        throw MatrixException("Cannot create a matrix with size 0");
    }
}

Matrix::Matrix(const vector<double> &data, bool row) : Matrix(vec2mat(data, row)) {}

#pragma region operators

vector<double> Matrix::operator[](int i) const{
    return data[i];
}

Matrix Matrix::operator-() const{
    vector<vector<double>> result;
    result.reserve(shape.first);
    for (const vector<double> &i : data) {
        vector<double> row;
        row.reserve(shape.second);
        for (double j : i) {
            row.push_back(-j);
        }
        result.push_back(row);
    }
    return Matrix(result);
}

Matrix Matrix::operator+(const Matrix &other) const{
    if (shape != other.shape) {
        throw MatrixException("Cannot add matrices of different shapes");
    }
    vector<vector<double>> result;
    result.reserve(shape.first);
    for (int i = 0; i < shape.first; i++) {
        vector<double> row;
        row.reserve(shape.second);
        for (int j = 0; j < shape.second; j++) {
            row.push_back(data[i][j] + other[i][j]);
        }
        result.push_back(row);
    }
    return Matrix(result);
}

Matrix Matrix::operator-(const Matrix &other) const{
    if (shape != other.shape) {
        throw MatrixException("Cannot subtract matrices of different shapes");
    }
    vector<vector<double>> result;
    result.reserve(shape.first);
    for (int i = 0; i < shape.first; i++) {
        vector<double> row;
        row.reserve(shape.second);
        for (int j = 0; j < shape.second; j++) {
            row.push_back(data[i][j] - other[i][j]);
        }
        result.push_back(row);
    }
    return Matrix(result);
}

Matrix Matrix::operator*(const Matrix &other) const{
    if (shape.second != other.shape.first) {
        throw MatrixException("Cannot multiply matrices of incompatible shapes");
    }
    vector<vector<double>> result;
    result.reserve(shape.first);
    for (int i = 0; i < shape.first; i++) {
        vector<double> row;
        row.reserve(other.shape.second);
        for (int j = 0; j < other.shape.second; j++) {
            double sum = 0;
            for (int k = 0; k < shape.second; k++) {
                sum += data[i][k] * other[k][j];
            }
            row.push_back(sum);
        }
        result.push_back(row);
    }
    return Matrix(result);
}

Matrix Matrix::operator*(double scalar) const{
    vector<vector<double>> result;
    result.reserve(shape.first);
    for (const vector<double> &i : data) {
        vector<double> row;
        row.reserve(shape.second);
        for (double j : i) {
            row.push_back(j * scalar);
        }
        result.push_back(row);
    }
    return Matrix(result);
}

Matrix Matrix::operator/(double scalar) const{
    return *this * (1 / scalar);
}

bool Matrix::operator==(const Matrix &other) const{
    if (shape != other.shape) {
        return false;
    }
    for (int i = 0; i < shape.first; i++) {
        for (int j = 0; j < shape.second; j++) {
            if (data[i][j] != other[i][j]) {
                return false;
            }
        }
    }
    return true;
}

Matrix Matrix::transpose() const{
    vector<vector<double>> result;
    result.reserve(shape.second);
    for (int i = 0; i < shape.second; i++) {
        vector<double> row;
        row.reserve(shape.first);
        for (int j = 0; j < shape.first; j++) {
            row.push_back(data[j][i]);
        }
        result.push_back(row);
    }
    return Matrix(result);
}

Matrix Matrix::row(int i) const{
    return Matrix({data[i]});
}

Matrix Matrix::col(int i) const {
    vector<vector<double>> result;
    result.reserve(shape.first);
    for (const vector<double> &j: data) {
        result.push_back({j[i]});
    }
    return Matrix(result);
}

Matrix Matrix::times(const Matrix &other) const {
    if (shape != other.shape) {
        throw MatrixException("Cannot element-wise multiply matrices of different shapes");
    }
    vector<vector<double>> result;
    result.reserve(shape.first);
    for (int i = 0; i < shape.first; i++) {
        vector<double> row;
        row.reserve(shape.second);
        for (int j = 0; j < shape.second; j++) {
            row.push_back(data[i][j] * other[i][j]);
        }
        result.push_back(row);
    }
    return Matrix(result);
}

ostream &operator<<(ostream &os, const Matrix &matrix) {
    for (const vector<double> &i : matrix.data) {
        for (double j : i) {
            os << j << " ";
        }
        os << endl;
    }
    return os;
}

#pragma endregion operators