#include "ga.h"
#include "utils.h"
#include <stdio.h>

//#define USE_NEURON_BIAS
#define USE_X
//#define SHOW_SORT


int _compare (const void * a, const void * b)
{
  struct Network *p_network_a = *(Network**)a;
  struct Network *p_network_b = *(Network**)b;
#ifdef SHOW_SORT
  printf("\t|  a: %.3f\t\tb: %.3f  |\n", p_network_b ->fitness, p_network_a->fitness);
#endif
  return (p_network_b->fitness - p_network_a->fitness);
}

/**
 * @brief nn_clone
 * @param p_nn_src
 * @param p_nn_dst
 */
void nn_clone(Network *p_nn_src, Network *p_nn_dst){
    for(int i = 0; i < p_nn_src->network_size; ++i){
        p_nn_dst->layers[i]->b = p_nn_src->layers[i]->b;
        for (int ii = 0; ii < p_nn_src->layers[i]->layer_size; ++ii) {
            p_nn_dst->layers[i]->neurons[ii].w = p_nn_src->layers[i]->neurons[ii].w;
#ifdef USE_X
            p_nn_dst->layers[i]->neurons[ii].x = p_nn_src->layers[i]->neurons[ii].x;
#endif
#ifdef USE_NEURON_BIAS
            p_nn_dst->layers[i]->neurons[ii].n_b = p_nn_src->layers[i]->neurons[ii].n_b;
#endif
        }
    }
}

/**
 * @brief nn_crossover
 * @param p_nn_a
 * @param p_nn_b
 * @param max_percent_outof_mid
 */
//TODO assignemnts and usages should probably each be isolated - because of more efficient cache utilitzation
void nn_crossover(Network *p_nn_a, Network *p_nn_b, int max_percent_outof_mid){
    for(int i = 0; i < p_nn_a->network_size; ++i){
        int delim = p_nn_a->network_size * ((float)(max_percent_outof_mid / 100.));
        for(int ii = 0; ii < p_nn_a->layers[i]->layer_size; ++ii){
            if (ii < delim){
                float tmp_w = p_nn_a->layers[i]->neurons[ii].w;
                p_nn_b->layers[i]->neurons[ii].w = tmp_w;
#ifdef USE_X
                float tmp_x = p_nn_a->layers[i]->neurons[ii].x;
                p_nn_b->layers[i]->neurons[ii].x = tmp_x;
#endif
#ifdef USE_NEURON_BIAS
                float tmp_b = p_nn_a->layers[i]->neurons[ii].n_b;
                p_nn_b->layers[i]->neurons[ii].n_b = tmp_b;
#endif
            } else {
                float tmp_w = p_nn_b->layers[i]->neurons[ii].w;
                p_nn_a->layers[i]->neurons[ii].w = tmp_w;
#ifdef USE_X
                float tmp_x = p_nn_b->layers[i]->neurons[ii].x;
                p_nn_a->layers[i]->neurons[ii].x = tmp_x;
#endif
#ifdef USE_NEURON_BIAS
                float tmp_b = p_nn_b->layers[i]->neurons[ii].n_b;
                p_nn_a->layers[i]->neurons[ii].n_b = tmp_b;
#endif
            }
        }
    }
}

/**
 * @brief nn_mutate
 * @param p_nn
 * @param max_abs_deviation
 */
void nn_mutate(Network *p_nn, float max_abs_deviation){
    for (int i = 0; i < p_nn->network_size; ++i){
        for(int ii = 0; ii < p_nn->layers[i]->layer_size; ++ii){
            float devt_w = get_random_float(max_abs_deviation) * (get_random_float(1) < .5 ? -1. : 1);
            p_nn->layers[i]->neurons[ii].w = p_nn->layers[i]->neurons[ii].w + devt_w;
#ifdef USE_NEURON_BIAS
            float devt_b = get_random_float(max_abs_deviation) * (get_random_float(1) < .5 ? -1. : 1);
            p_nn->layers[i]->neurons[ii].n_b = p_nn->layers[i]->neurons[ii].n_b + devt_b;
#endif
        }
    }
}

/**
 * @brief pop_sort
 * @param p_population
 */
void pop_sort(Population *p_population){
    qsort (p_population->networks, p_population->population_size, sizeof(p_population->networks[0]), _compare);
}

/**
 * @brief pop_clone
 * @param p_population
 * @param survival_rate
 */
void pop_clone(Population *p_population, int survival_rate){
    //rand_init();
//    pop_sort(p_population);
    for(int i = survival_rate; i < p_population->population_size; ++i){
        int picker = (int)get_random_float(survival_rate);
        nn_clone(p_population->networks[i], p_population->networks[picker]);
    }
}

/**
 * @brief pop_crossover
 * @param p_population
 */
void pop_crossover(Population *p_population, float max_percent_of_pop, float max_percent_outof_mid){
    int pop_part = (int)(p_population->population_size * (max_percent_of_pop / 100.f));
    for(int i = 0; i < pop_part; ++i){
        int picker = (int)get_random_float(p_population->population_size);
        int max_outof_mid = (int)(max_percent_outof_mid * i / pop_part);
        nn_crossover(p_population->networks[i], p_population->networks[picker], max_outof_mid);
    }
}

/**
 * @brief pop_mutate
 * @param p_population
 * @param max_abs_deviation
 */
void pop_mutate(Population *p_population, float max_abs_deviation){
    for(int i = 0; i < p_population->population_size; ++i){
        float devtn = get_random_float(max_abs_deviation);
        nn_mutate(p_population->networks[i], devtn);
    }
}

/**
 * @brief clone_entire_population
 * @param p_p0
 * @param p_p1
 */
void clone_entire_population(Population* p_p0, Population* p_p1){
    for(int i = 0; i < p_p0->population_size; ++i){
        for (int ii = 0; ii < p_p0->networks[i]->network_size; ++ii) {
            p_p1->networks[i]->layers[ii]->b = p_p0->networks[i]->layers[ii]->b;
            for (int iii = 0; iii < p_p0->networks[i]->layers[ii]->layer_size; ++iii) {
                p_p1->networks[i]->layers[ii]->neurons[iii].w = p_p0->networks[i]->layers[ii]->neurons[iii].w;
                p_p1->networks[i]->layers[ii]->neurons[iii].x = p_p0->networks[i]->layers[ii]->neurons[iii].x;
            }
        }
    }
}

/**
 * @brief show_pop_diff
 * @param p_population0
 * @param p_population1
 */
void show_pop_diff(Population* p_population0, Population* p_population1){

    for (int i = 0; i < p_population0->population_size; ++i) {
        printf("network: %i\n", i);
        printf("fitness:");
        print_deviation("%.02f\n", p_population1->networks[i]->fitness - p_population0->networks[i]->fitness); // @d

        for (int ii = 0; ii < p_population0->networks[i]->network_size; ++ii) {
            printf("---------------------------------------------------\n");
            printf("b(l): ");
            print_deviation("%.02f\n", p_population1->networks[i]->layers[ii]->b - p_population0->networks[i]->layers[ii]->b); // @d
            printf("\nw:");

            for (int iii = 0; iii < p_population0->networks[i]->layers[ii]->layer_size; ++iii) {
                print_deviation("\t\t%.02f", p_population1->networks[i]->layers[ii]->neurons[iii].w - p_population0->networks[i]->layers[ii]->neurons[iii].w); // @d
            }
            printf("\nx:");

            for (int iii = 0; iii < p_population0->networks[i]->layers[ii]->layer_size; ++iii) {
                print_deviation("\t\t%.02f", p_population1->networks[i]->layers[ii]->neurons[iii].x - p_population0->networks[i]->layers[ii]->neurons[iii].x); // @d
            }

            printf("\n");

        }
        printf("===================================================\n");

    }

}
