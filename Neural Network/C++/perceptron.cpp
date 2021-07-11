#include "perceptron.h"

double frand() 
{
    return (2.0*(double)rand() / RAND_MAX) - 1.0;
}

Perceptron::Perceptron(int inputs, double _bias) 
{
    this->bias = _bias;
    this->weights.resize(inputs+1);
    generate(this->weights.begin(),this->weights.end(),frand);
}


//change name to fire?
double Perceptron::run(vector<double> x)
{
    //x.push_back(this->bias);   //optimize later to not have to add here ----> (done)
    //double sum = inner_product(x.begin(),x.end(),this->weights.begin(),(double)0.0) + (this->bias * weights[weights.size() -1]);
    return sigmoid(inner_product(x.begin(),x.end(),this->weights.begin(),(double)0.0) + (this->bias * this->weights.back()));
}

void Perceptron::set_weights(vector<double> w_init)
{

    //check if w_init is same size as this->weights
    if(w_init.size() != this->weights.size()) 
    {
        cerr << "set_weights: Vector size mismatch!" << endl;
        return;
    }

    // int index = 0;
    // for(double& w : this->weights)
    // {
    //     w = w_init[index++];
    // }
    weights = w_init;
}

double Perceptron::sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}


MultiLayerPerceptron::MultiLayerPerceptron(vector<int> layers, double bias, double eta)
{
    this->layers = layers;
    this->bias = bias;
    this->eta = eta;

    for(int i = 0; i < this->layers.size(); i++)
    {
        this->values.push_back(vector<double>(layers[i], 0.0));
        this->d.push_back(vector<double>(layers[i], 0.0));
        this->network.push_back(vector<Perceptron>());

        if(i > 0) //network[0] is the input layer, so no neurons
        {
            //  for(int j = 0; j < layers[i]; j++)
            //      network[i].push_back(Perceptron(layers[i-1], bias));
            
            network[i] = vector<Perceptron>(layers[i], Perceptron(layers[i-1],bias));
        }
    }
}


void MultiLayerPerceptron::set_weights(vector<vector<vector<double>>> w_init)
{
    for(int i = 0; i < w_init.size(); i++)
    {
        for(int j = 0; j < w_init[i].size(); j++)
        {
            this->network[i+1][j].weights = w_init[i][j];
        }
    }
}

void MultiLayerPerceptron::print_weights() 
{
    cout << endl;
    for(int i = 1; i < this->network.size(); i++) 
    {
        for(int j = 0; j < this->layers[i]; j++)
        {
            cout << "Layer " << i+1 << " Neuron " << j << ": ";
            for( auto &it : network[i][j].weights)
                cout << it << "\t";
            cout << endl;
        }
    }
    cout << endl;
}

vector<double> MultiLayerPerceptron::run(vector<double> x)
{
    this->values[0] = x;
    for(int i = 1; i < this->network.size(); i++)
    {
        for(int j = 0; j < this->network[i].size(); j++)
        {
                this->values[i][j] = this->network[i][j].run(this->values[i-1]);
        }
    }

    return this->values.back();
}



//BACKPROPAGATION
double MultiLayerPerceptron::backpropagation(vector<double> x, vector<double> y)
{
    //STEP 1: Feed a sample to the network
    vector<double> output = this->run(x);
    
    //STEP 2: Calculate the MSE
    double MSE;
    for(int i = 0; i < output.size(); i++)
    {
        MSE += (y[i] - output[i]) * (y[i] - output[i]);
    }
    MSE /= output.size();
    
    //STEP 3: Calculate the output error terms
    for(int n = 0; n < network.back().size(); n++)
    {
        this->d.back()[n] = output[n] * (1-output[n]) * (y[n]-output[n]);
    }

    //STEP 4: Calculate the error term of each unit on each layer
    for(int i = this->network.size()-2; i > 0; i--)
    {
        for(int h = 0; h < network[i].size(); h++)
        {
            double fwd_error = 0.0;
            for(int k = 0; k < this->layers[i+1]; k++)
            {
                fwd_error += network[i+1][k].weights[h] * this->d[i+1][k];
            }
            this->d[i][h] = values[i][h] * (1-values[i][h]) * fwd_error;
        }
    }

    //STEP 5 & 6: Calculate the deltas and update the weights
    for(int i = 1; i < network.size(); i++)
        for(int j = 0; j < layers[i]; j++)
            for(int k = 0; k < layers[i-1]+1; k++)
            {
                if(k==layers[i-1])
                    network[i][j].weights[k] += eta * d[i][j] * bias;
                else 
                    network[i][j].weights[k] += eta * d[i][j] * values[i-1][k];
            }

    
    return MSE;
}