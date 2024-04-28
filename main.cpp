#include <iostream>
#include "utils.h"

using namespace std;



int main() {

    try {
        Matrix m1({{1, 2, 3},
                  {4, 5, 6},
                  {7, 8, 9}});

        Matrix m2({{1, 2, 3},
                  {4, 5, 6},
                  {7, 8, 9}});

        vector<double> v1 = {1, -2, 3};
        cout << m1.shape.first << " " << m1.shape.second << endl;
        cout << m1.transpose();

        Matrix m3{v1};

        cout << relu(m3);
        cout << sigmoid(m3);
        cout << softmax(m3);

    }
    catch (MatrixException &e) {
        cout << e.what() << endl;
    }




}
