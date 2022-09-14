#ifndef NN_H
#define NN_H

#define ALPHA 0.3

typedef struct Neuron {
    float w;
#ifdef USE_NEURON_BIAS
    float n_b;
#endif
    float x;
} Neuron;

typedef struct Layer {
    Neuron* neurons;
    int layer_size;
    int layer_nr;
    float b;
} Layer;

typedef struct Network {
    Layer** layers;
    int network_size;
    float fitness;
} Network;

typedef struct Population {
    Network** networks;
    int population_size;
} Population;

Population* init_population(int pop_size);
Network* create_network(Population* p_population, int net_nr, int net_size);
Layer* create_layer(Network* p_net, int layer_nr, int layer_size);
Network* get_network(Population* p_population, int network_n);
Layer* get_layer(Network* p_network, int layer_n);
Neuron get_neuron(Layer* p_layer, int neuron_n);
void init_layer_weights(Layer* p_layer);
void init_pop_weights(Population* p_pop);
void delete_layer(Layer* p_layer);
void delete_network(Network* p_network);
void delete_population(Population* p_population);
float leaky_relu(float input);
float relu(float input);
float sigmoid(float input);
void dense_prop(Layer* input_layer, Layer* output_layer, float (*active_func)(float));
void forward_prop(Network* p_network);
void forward_prop_all(Population* p_population);
void show_network_status(Network* p_network, int net_nr);
void show_population_status(Population* p_population);


#endif // NN_H
