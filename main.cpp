#include <iostream>
#include "utils.h"

using namespace std;



int main() {

    try {
        Matrix m1 = random_init(3, 3);
        Matrix m2 = zeros(3, 3);

        vector<double> v1 = {1, -2, 3};

        Matrix m3 = diag(one_hot(3, 5));
        cout << m3;

    }
    catch (MatrixException &e) {
        cout << e.what() << endl;
    }




}
