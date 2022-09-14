#include <stdlib.h>
#include <stdio.h>
#include "nn.h"
#include "show.h"
#include "utils.h"
#include "math.h"

/**
 * @brief create_population
 * @param pop_size
 * @return
 */
Population* init_population(int pop_size){
    Population* p_population = (Population*)malloc(sizeof (Population));
    p_population ->population_size = pop_size;
    p_population ->networks = (Network**)malloc(sizeof (Network*) * pop_size);
    return p_population ;
}

/**
 * @brief create_network
 * @param p_population
 * @param net_nr
 * @param net_size
 * @return
 */
Network* create_network(Population* p_population, int net_nr, int net_size){
    p_population->networks[net_nr] = (Network*)malloc(sizeof (Network));
    p_population->networks[net_nr]->layers = (Layer**)malloc(sizeof (Layer*) * net_size);
    p_population->networks[net_nr]->network_size = net_size;
    return p_population->networks[net_nr];
}

/**
 * @brief create_layer
 * @param p_net
 * @param layer_nr
 * @param layer_size
 * @return
 */
Layer* create_layer(Network* p_net, int layer_nr, int layer_size){
    p_net->layers[layer_nr] = (Layer*)malloc(sizeof (Layer));
    p_net->layers[layer_nr]->layer_nr = layer_nr;
    p_net->layers[layer_nr]->neurons = (Neuron*)malloc(sizeof (Neuron) * layer_size);
    p_net->layers[layer_nr]->layer_size = layer_size;
    return p_net->layers[layer_nr];
}

/**
 * @brief get_network
 * @param p_population
 * @param network_n
 * @return
 */
Network* get_network(Population* p_population, int network_n){
    return p_population->networks[network_n];
}

/**
 * @brief get_layer
 * @param p_network
 * @param layer_n
 * @return
 */
Layer* get_layer(Network* p_network, int layer_n){
    return p_network->layers[layer_n];
}

/**
 * @brief get_neuron
 * @param p_layer
 * @param neuron_n
 * @return
 */
Neuron get_neuron(Layer* p_layer, int neuron_n){
    return p_layer->neurons[neuron_n];
}

/**
 * @brief init_weights
 * @param p_layer
 */
void init_layer_weights(Layer* p_layer){
    for(int i = 0; i < p_layer->layer_size; ++i){
        p_layer->neurons[i].w = get_random_float(1.f);
    }
}

/**
 * @brief init_pop_weights
 * @param p_pop
 */
void init_pop_weights(Population* p_pop){
    for(int i = 0; i < p_pop->population_size; ++i){
        for(int ii = 0; ii < p_pop->networks[i]->network_size; ++ii) {
            init_layer_weights(p_pop->networks[i]->layers[ii]);
        }
    }
}

/**
 * @brief delete_layer
 * @param p_layer
 */
void delete_layer(Layer* p_layer){
    free(p_layer->neurons);
    free(p_layer);
}

/**
 * @brief delete_network
 * @param p_network
 */
void delete_network(Network* p_network){
    for(int i = 0; i < p_network->network_size; ++i){
        delete_layer(p_network->layers[i]);
    }
    free(p_network);
}

/**
 * @brief delete_population
 * @param p_population
 */
void delete_population(Population* p_population){
    for(int i = 0; i < p_population->population_size; ++i){
        delete_network(p_population->networks[i]);
    }
    free(p_population);
}

/**
 * @brief leaky_relu
 * @param input
 * @return
 */
float leaky_relu(float input){
    if (input < 0) return ALPHA * input;
    return input;
}

/**
 * @brief relu
 * @param input
 * @return
 */
float relu(float input){
    if (input < 0) return 0;
    return input;
}

/**
 * @brief sigmoid
 * @param input
 * @return
 */
float sigmoid(float input){
    return 1.f / (1.f + exp(-input));
}

/**
 * @brief dense_prop
 * @param input_layer
 * @param output_layer
 */
void dense_prop(Layer* input_layer, Layer* output_layer, float (* active_func)(float)){
    for(int i = 0; i < output_layer->layer_size; ++i){
        float sum = 0;
        for(int j = 0; j < input_layer->layer_size; ++j){
            sum += input_layer->neurons[i].w * input_layer->neurons[j].x;
        }
        output_layer->neurons[i].x += (active_func(sum + input_layer->b));
    }
}

/**
 * @brief forward_prop
 * @param p_network
 */
void forward_prop(Network* p_network){
    for (int i = 0; i < p_network->network_size - 1; ++i){
        dense_prop(p_network->layers[i], p_network->layers[i + 1], leaky_relu);
    }
}

/**
 * @brief forward_prop_all
 * @param p_population
 */
void forward_prop_all(Population* p_population){
    for(int i = 0; i < p_population->population_size; ++i){
        forward_prop(p_population->networks[i]);
    }
}

/**
 * @brief show_network_summary
 * @param p_network
 * @param netNr
 */
void show_network_status(Network* p_network, int net_nr) {
    printf("\nNetwork Nr.: %i, fitness: %.2f\n", net_nr, p_network->fitness);
    for (int i = 0; i < p_network->network_size; ++i){
        printf("\n\tLayer Nr.: %i\n", i);
        printf("\tBias: %.3f\n", p_network->layers[i]->b);
        printf("\tWeights:\t ");
        for (int ii = 0; ii < p_network->layers[i]->layer_size; ++ii){
            printf("\t%.3f", p_network->layers[i]->neurons[ii].w);
        }
        printf("\n\tX:\t\t");
        for (int ii = 0; ii < p_network->layers[i]->layer_size; ++ii){
            printf("\t%.3f", p_network->layers[i]->neurons[ii].x);
        }
        printf("\n");
    }
    printf("\n\n");
}

/**
 * @brief population_summary
 * @param p_population
 */
void show_population_status(Population* p_population){
    for(int i = 0; i < p_population->population_size; ++i){
        show_network_status(p_population->networks[i], i);
    }
}
