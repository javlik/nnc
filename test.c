#include <stdio.h>
#include <stdlib.h>
#include "nn.h"
#include "ga.h"
#include "show.h"
#include "utils.h"

//#define NN_SHOW
//#define GA_SHOW
#define DIFF_SHOW

#define C_POP_SIZE 10
#define C_NET_SIZE 4

const int CA_LAYER_CONFIG[] = {5, 4, 3, 2};

Population *p_population_0, *p_population_1;


/**
 * @brief test_nn
 */
void test_nn(Population* p_p) {

    for (int i = 0; i < C_POP_SIZE; ++i){
        Network* p_network = create_network(p_p, i, C_NET_SIZE);
        p_network->fitness = i;
        for (int ii = 0; ii < C_NET_SIZE; ++ii){
            Layer* p_layer = create_layer(p_network, ii, CA_LAYER_CONFIG[ii]);
            init_layer_weights(p_layer);
        }

        p_network->layers[0]->neurons[0].x = 0.5; // one input point set to a value
    }

    forward_prop_all(p_p);
#ifdef NN_SHOW
    show_population_summary(p_p);
#endif
}


/**
 * @brief test_gen
 */
void test_ga(Population* p_p) {
    printf("------------ after clone -------------\n\n");
    pop_clone(p_p, 2);
#ifdef GA_SHOW
    show_population_summary(p_p);
#endif
}

/**
 * @brief test_diff
 * @param p_p0
 * @param p_p1
 */
void test_diff(Population* p_p0, Population* p_p1){
    show_pop_diff(p_p0, p_p1);
}


/**
 * @brief main
 * @return
 */
int main()
{
    p_population_0 = init_population(C_POP_SIZE);
    p_population_1 = init_population(C_POP_SIZE);
    test_nn(p_population_0);
    test_nn(p_population_1);
    test_ga(p_population_0);
    clone_entire_population(p_population_0, p_population_1);
#ifdef DIFF_SHOW
//    init_pop_weights(p_population_1); // randomize weights in whole population
    test_diff(p_population_0, p_population_1);
#endif
    delete_population(p_population_0);
    delete_population(p_population_1);
//  main_vis_loop();
    return 0;
}

