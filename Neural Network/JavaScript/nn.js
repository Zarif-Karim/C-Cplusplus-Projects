var inputs = [  [1, 2, 3, 2.5],
                [2.0, 5.0, -1.0, 2.0],
                [-1.5, 2.7, 3.3, -0.8]
            ];

var weights = [ [0.2, 0.8, -0.5, 1.0],
                [0.5, -0.91, 0.26, -0.5],
                [-0.26, -0.27, 0.17, 0.87]
            ];                

var biases = [2, 3, 0.5];

var weights2 = [ [0.1, -0.14, 0.5],
                [-0.5, 0.12, -0.33],
                [-0.44, 0.73, -0.13]
            ];                

var biases2 = [-1, 2, -0.5];

// var layer_outputs = []; //output of current layer
// for (var i = 0; i < biases.length; i++){  //weights.length could also be used!
//     var neuron_output = 0;
//     for(var j = 0; j < inputs.length; j++){
//         neuron_output += inputs[j] * weights[i][j];
//     }
//     neuron_output += biases[i];
//     layer_outputs.push(neuron_output);
// }

var layer1_outputs = dotproduct_plusBias(inputs, weights, biases);
var layer2_outputs = dotproduct_plusBias(layer1_outputs, weights2, biases2);

console.log(layer2_outputs); 




//utilities-----------------v

function dotproduct_plusBias(inputs, weights, biases) {
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