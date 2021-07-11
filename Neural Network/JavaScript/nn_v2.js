//utilities-----------------

function dotProductPlusBias(inputs, weights, biases) {
    var layer_outputs = []; //output of current layer
    
    for (var i = 0; i < inputs.length; i++){  //weights.length could also be used!
        var current_layer_output = [];
        
        for (var k = 0; k < weights.length; k++){
            var input = inputs[i];
            var weight = weights[k];
            var neuron_output = 0;

            for(var j = 0; j < weight.length; j++){
                neuron_output += input[j] * weight[j];
            }
            neuron_output += biases[k];
            current_layer_output.push(neuron_output);
        }
        layer_outputs.push(current_layer_output);
    }

    return layer_outputs;
}


function random_matrix(rows, columns, min_value, max_value) {
    var rand_matrix = [];
    for(var row = 0; row < rows; row++){
        rand_matrix.push([]);
        for(var col = 0; col < columns; col++){
            rand_matrix[row].push(Math.random() * (max_value-min_value) + min_value);
        }
    }

    if(rand_matrix.length == 1) return rand_matrix[0]; //if one row return that as 1D vector
    return rand_matrix; //else return random matrix 2D vector
}


function create_data(points, classes) {
    var x = random_matrix(points*classes,2, 0, 0);
    //var y = 
}
// end utilities--------------

//class definitions---------

class Layer_Dense {
    constructor(n_inputs, n_neurons) {
        this.weights = random_matrix(n_neurons, n_inputs, -1,1);
        this.biases = random_matrix(1,n_neurons, 0,0);//zero initialise
    }

    forward(inputs) {
        this.output = dotProductPlusBias(inputs, this.weights, this.biases);
    }
}

class Activation_ReLu {

    forward(inputs) {
        this.output = [];
        for(let i = 0; i < inputs.length; i++) {
            this.output.push([]);
            for(let j = 0; j < inputs[i].length; j++) {
                this.output[i].push(Math.max(0,inputs[i][j]));
            }
        }
    }
}

class Activation_SoftMax {

    forward(inputs) {
        this.output = [];
        for(let i = 0; i < inputs.length; i++) {
            this.output.push([]);
            var input_max = inputs[i].reduce(function(a,b){return Math.max(a,b);});
            for(let j = 0; j < inputs[i].length; j++) {
                //add the exponents
                this.output[i].push(Math.exp(inputs[i][j] - input_max));
            }
            //normalise
            var expSum = this.output[i].reduce(function(a,b){return a + b;}, 0);
            for(let j = 0; j < this.output[i].length; j++) {
                //devide the exponents by sum
                this.output[i][j] = this.output[i][j]/expSum;
            }

        }
    }
}


//End class definitions

var X = [   
    [1, 2, 3, 2.5],
    [2.0, 5.0, -1.0, 2.0],
    [-1.5, 2.7, 3.3, -0.8]
];


//console.log("random_matrix: \n", random_matrix(4,3,-1,1));
//console.log("zero_biases: \n", random_matrix(1,3,0,0));

var layer1 = new Layer_Dense(4,5);
var reLu = new Activation_ReLu();
var layer2 = new Layer_Dense(5,2);
var softMax = new Activation_SoftMax();

layer1.forward(X);
console.log("layer1: \n",layer1.output);
reLu.forward(layer1.output);
console.log("\nReLu: \n",reLu.output);
layer2.forward(reLu.output);
console.log("layer2: \n",layer2.output);
softMax.forward(layer2.output);
console.log("\softMax: \n",softMax.output);


/*

zak
var c = 1.15 - a*Math.log10(0+b) 
var a = -(1.15 - a*Math.log10(0+b))/Math.log10(-2.05+b) ;
Math.log10(-2.87+b) = (-1.72 - c) / a;

*/

