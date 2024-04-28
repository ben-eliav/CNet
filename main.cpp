#include <iostream>
#include "utils.h"

using namespace std;



int main() {

    try {
        Matrix m1 = random_init(3, 3);
        Matrix m2 = zeros(3, 3);

        //time the function
        auto start = chrono::high_resolution_clock::now();
        Matrix m3 = read_data_csv("../data.csv", "label").first;  // data is in the parent directory of cmake-build-debug
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Elapsed time: " << elapsed.count() << " s\n";
        cout << m3;

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