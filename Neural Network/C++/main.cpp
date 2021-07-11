#include "perceptron.cpp"

int main()
{
    //random seed
    //srand(time(0));
    
    //for testing
    srand(0);


    //Perceptron test(2);
    //test.set_weights({10,10,-15}); //AND Gate
    //test.set_weights({-10,-10,15}); //NAND Gate
    //test.set_weights({15,15,-10}); //OR Gate
    //test.set_weights({-15,-15,10}); //NOR Gate

    // cout << "Gate: " << endl;
    // for(double i = 0; i < 2; i++){
    //     for(double j = 0; j < 2; j++) {
    //         cout << test.run({i,j}) << endl;
    //     }
    // }

    /*
        Making an XOR gate:
        2 binary inputs as above
        1 hidden and 1 ouput layer

        hidden layer: NAND and OR 
        output layer: AND    
    */
    
    //V_1
    // Perceptron n(2),o(2),a(2);
    // n.set_weights({-10,-10,15}); //NAND
    // o.set_weights({15,15,-10}); //OR
    // a.set_weights({10,10,-15}); //AND

    // cout << "Gate: " << endl;
    // for(double i = 0; i < 2; i++){
    //     for(double j = 0; j < 2; j++) {
    //         cout << a.run({o.run({i,j}),n.run({i,j})}) << endl;
    //     }
    // }

    //V_2
    MultiLayerPerceptron *mp = new MultiLayerPerceptron({2,2,1});
    
    // vector<vector<vector<double>>> weights;
    // weights.push_back(vector<vector<double>>());//first hidden weights
    // weights[0].push_back({-10,-10,15});
    // weights[0].push_back({15,15,-10});
    // weights.push_back(vector<vector<double>>());//output weights
    // weights[1].push_back({10,10,-15});
    
    // mp->set_weights(weights);
    // mp->set_weights({{{-10,-10,15},{15,15,-10}},{{10,10,-15}}});

    // mp->print_weights();


    // cout << "Gate: " << endl;
    // for(double i = 0; i < 2; i++){
    //     for(double j = 0; j < 2; j++) {
    //         cout << mp->run({i,j})[0] << endl;
    //     }
    // }



    //V_3
    //with implemented back prop

    double MSE;
    for(int i = 0; i < 3000; i++)
    {
        MSE = 0.0;
        MSE += mp->backpropagation({0,0},{0});
        MSE += mp->backpropagation({0,1},{1});
        MSE += mp->backpropagation({1,0},{1});
        MSE += mp->backpropagation({1,1},{0});
        MSE /= 4.0;

        if(i%100 == 0) cout << "MSE = " << MSE << endl;
    }

    cout << "\n\nTrained weights:\n\n";
    mp->print_weights();

    cout << "Gate: " << endl;
    for(double i = 0; i < 2; i++){
        for(double j = 0; j < 2; j++) {
            cout << mp->run({i,j})[0] << endl;
        }
    }

    return 0;
}