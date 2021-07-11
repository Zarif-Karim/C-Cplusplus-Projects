class Neuron {
    constructor(n_input) {
        this.weights = [];
        for(let i = 0; i < n_input; i++) {
               this.weights.push((Math.random() * 2) -1);
        }
        this.bias = (Math.random() * 2) -1;
    }

    fire(inputs) {
        this.output = 0;
        for(let i = 0; i < inputs.length; i++){
            this.output += inputs[i] * this.weights[i];
            //console.log(this.output);
        }
        this.output += this.bias;

        return this.output;
    }
}

class Dense_layer{
    constructor(n_nodes, n_inputs, activation){
        this.activation = activation;
        this.nodes = [];
        for(let i = 0; i < n_nodes; i++){
            this.nodes.push(new Neuron(n_inputs));
        }
    }

    feed(inputs, dontActivate) {
        for(let n = 0; n < this.nodes.length; n++){
            this.nodes[n].fire(inputs);
        }
        if(!dontActivate)this.activate();
        else {
            this.output = new Array(this.nodes.length);
            for(let i = 0; i < this.nodes.length; i++){
                this.output[i] = this.nodes[i].output;
            }
        }
    }

    activate() {
        this.output = new Array(this.nodes.length);
        for(let i = 0; i < this.nodes.length; i++){
            this.output[i] = this.nodes[i].output;
        }
        //reLu
        if(this.activation == 'ReLu'){
            for(let i = 0; i < this.nodes.length; i++){
                this.output[i] = (Math.max(0,this.nodes[i].output));
            }
        } else if(this.activation == 'SoftMax'){
            var max = this.output.reduce(function(a,b){return Math.max(a,b);});
            for(let j = 0; j < this.output.length; j++) {
                //add the exponents
                this.output[j] = (Math.exp(this.output[j] - max));
            }
            //normalise
            var expSum = this.output.reduce(function(a,b){return a + b;}, 0);
            for(let j = 0; j < this.output.length; j++) {
                //devide the exponents by sum
                this.output[j] = this.output[j]/expSum;
            }
        }
    }
}

class Network {
    constructor(n_inputs, n_layers, options) {
        this.layers = [new Dense_layer(options[0][0],n_inputs,options[0][1])]
        for(let i = 1; i < n_layers; i++){
            this.layers.push(new Dense_layer(options[i][0], this.layers[i-1].nodes.length, options[i][1]));
        }
    }

    forward(inputs) {
        this.layers[0].feed(inputs);
        for(let i = 1; i < this.layers.length; i++){
            this.layers[i].feed(this.layers[i-1].output);
        }
    }

    predict(inputs) {
        this.forward(inputs);
        return this.layers[this.layers.length-1].output;
    }
}


//testing environment:
// let grid = [
//     [0,0,0,0,0],
//     [8,8,0,0,0],
//     [0,0,0,0,0],
//     [0,0,0,0,5],
//     [0,0,0,0,0]
// ];
// // 0 1 2 3
// // u d l r
// let dir = 3;

// let inputs = grid.flat();
// console.log(inputs * 0.1);
//inputs.push(dir);

// let options = [[32,'ReLu'],[32,'ReLu'],[4,'SoftMax']];
// let nn = new Network(inputs.length, 3, options);

// let prediction = nn.predict(inputs);

// console.log(prediction);


//pass--------------
// let testNeuron = new Neuron(inputs.length);
// console.log(testNeuron.fire(inputs));

// let testLayer = new Dense_layer(16,inputs.length,'ReLu');
// let testLayer1 = new Dense_layer(16,testLayer.nodes.length,'ReLu');
// let testLayer2 = new Dense_layer(4,testLayer1.nodes.length,'ReLu');
// testLayer.feed(inputs);
// console.log(testLayer.output);
// testLayer1.feed(testLayer.output);
// console.log(testLayer1.output);
// testLayer2.feed(testLayer1.output, true);
// console.log(testLayer2.output);