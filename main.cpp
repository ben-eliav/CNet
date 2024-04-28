#include <iostream>
#include "utils.h"

using namespace std;



int main() {

    try {
        Matrix m1 = random_init(3, 3);
        Matrix m2 = zeros(3, 3);

        vector<double> v1 = {1, -2, 3};
        cout << m1.shape.first << " " << m1.shape.second << endl;
        cout << m1.transpose();

        Matrix m3{v1};

        cout << relu(m1);
        cout << m2;

    }
    catch (MatrixException &e) {
        cout << e.what() << endl;
    }




}
