//
// Created by Ben on 28/04/2024.
//

#ifndef NEURALNETWORK_DATAFRAME_H
#define NEURALNETWORK_DATAFRAME_H

#include <utility>
#include <vector>
#include <iterator>

using namespace std;

//class Tensor {
//    vector<int> shape;  // list, the length of the vector is the dimension of the tensor
//    ;
//
//};

#pragma region Exceptions

class MatrixException : public exception {
    char const *message;

public:
    MatrixException(char const *msg);
    char* what();

};

#pragma endregion Exceptions

inline vector<vector<double>> vec2mat(const vector<double>& vec);

#pragma region Matrix

class Matrix {
    vector<vector<double>> data;

public:
    pair<size_t, size_t> shape;

    explicit Matrix(vector<vector<double>> data);
    explicit Matrix(const vector<double> &data, bool row = false);
    vector<double> operator[](int i) const;
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;
    bool operator==(const Matrix &other) const;
    Matrix transpose() const;
    Matrix operator-() const;
    Matrix row(int i) const;
    Matrix col(int i) const;
    Matrix times(const Matrix &other) const;
    friend ostream &operator<<(ostream &os, const Matrix &matrix);

    vector<vector<double>>::const_iterator begin() const {
        return data.begin();
    }
    vector<vector<double>>::const_iterator end() const {
        return data.end();
    }
};



#pragma endregion Matrix

#endif //NEURALNETWORK_DATAFRAME_H
