#ifndef NN_H
#define NN_H

typedef struct Neuron {
    float w;
    float b;
    float x;
    float y;
} Neuron;

typedef struct Layer {
    Neuron* neurons;
    int layerSize;
    int layerNr;
} Layer;

typedef struct Network {
    Layer* layers;
    int networkSize;
    int NetworkNr;
} Network;


// On the top of the final hierarchy, there will be a population of Networks
// ... but probably in another header file


#endif // NN_H
