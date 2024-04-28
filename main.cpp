#include <iostream>
#include "neuralnetwork.h"


using namespace std;



int main() {

    try {
        Matrix m1 = zeros(3, 3);
        Matrix m2 = zeros(3, 1);
        cout << m1 * m2 << endl;

        cout << "***********************" << endl;

        NeuralNetwork nn({3, 3, 2}, 0.01);
        auto p = read_data_csv("../data.csv", "label");
        cout << p.first.shape.first << " " << p.first.shape.second << endl;
        cout << p.first.row(1).shape.first << " " << p.first.row(1).shape.second << endl;
        cout << p.first;

        cout << "***********************" << endl;
        nn.forward(p.first.row(1));
    }
    catch (MatrixException &e) {
        cout << e.what() << endl;
    }




}


//#include <iostream>
//#include <sstream>
//#include<string>
//using namespace std;
//
//void print(string str)
//{
//    stringstream s(str);
//    string num;
//
//    int count = 0;
//    while (getline(s, num,','))
//    {
//        cout<<num<<" ";
//    }
//
//}
//
//
//int main()
//{
//    string s = "132456,2,3,4";
//    print(s);
//    return 0;
//}