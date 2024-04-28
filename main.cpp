#include <iostream>
#include "neuralnetwork.h"
#define EPOCHS 1000

using namespace std;



int main() {

    try {


        auto p = read_data_csv("../data.csv", "label");
        NeuralNetwork nn({3, 4, 3, 2}, 0.01, p.first.shape.first);
        cout << "***********************" << endl;
        vector<pair<Matrix, int>> dataloader;
        dataloader.reserve(p.first.shape.first);
        for (int i = 0; i < p.first.shape.first; i++) {
            dataloader.emplace_back(p.first.row(i), (int)p.second.row(i)[0][0]);
        }

        vector<double> loss_per_epoch(EPOCHS, 0);
//        for (int epoch = 0; epoch < EPOCHS; epoch++) {
//            for (auto data = dataloader.begin(); data != dataloader.end(); data++) {
//                auto out = nn.forward(&data->first);
//                loss_per_epoch[epoch] += cross_entropy_loss(data->second, out);
//                nn.backpropagate(data->first, data->second, out);
//                break;
//            }
//            cout << "Epoch: " << epoch << " Loss: " << loss_per_epoch[epoch] << endl;
//        }


        for (int epoch = 0; epoch < EPOCHS; epoch++) {
            loss_per_epoch[epoch] = 0;
            for (auto data = dataloader.begin(); data != dataloader.end(); data++) {
                auto out = nn.forward(&data->first);
                loss_per_epoch[epoch] += cross_entropy_loss(data->second, out) / dataloader.size();
                cout << "Loss: " << cross_entropy_loss(data->second, out) << endl;
                nn.backpropagate(data->first, data->second, out);
            }
            cout << "Epoch: " << epoch << " Loss: " << loss_per_epoch[epoch] << endl;
        }



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