class NNlayers {
    constructor(input_size, output_size, activation, lr = 0.001) {
        this.input_size = input_size;
        this.output_size = output_size;
        this.weights = [];
        for(let i = 0; i < output_size * input_size; i++) {

        }


        np.random.uniform(low=-0.5, high=0.5, size=(input_size, output_size));
        if(activation) this.activation_function = activation;
        else this.activation_function = null;
        if(lr) this.lr = lr;
        else lr = 0.001;
    }
}
