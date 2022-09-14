#ifndef GEN_H
#define GEN_H

#include "nn.h"

int _compare (const void * a, const void * b);
void nn_clone(Network* p_nn_src, Network* p_nn_dst);
void nn_crossover(Network* p_nn_a, Network* p_nn_b, int max_percent_outof_mid);
void nn_mutate(Network* p_nn, float max_abs_deviation);

void pop_sort(Population *p_population);
void pop_clone(Population* p_population, int survival_rate);
void pop_crossover(Population *p_population, float max_percent_of_pop, float max_percent_outof_mid);
void pop_mutate(Population* p_population, float max_abs_deviation);

void clone_entire_population(Population* p_p0, Population* p_p1);

void show_pop_diff(Population* p_population0, Population* p_population1);

#endif // GEN_H
