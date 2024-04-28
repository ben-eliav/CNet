#include <iostream>
#include "utils.h"

using namespace std;



int main() {

    try {
        Matrix m1 = random_init(3, 3);
        Matrix m2 = zeros(3, 3);

        vector<double> v1 = {1, -2, 3};

        Matrix m3{v1};
        cout << d_sigmoid(m3) << endl;


    }
    catch (MatrixException &e) {
        cout << e.what() << endl;
    }




}
