#ifndef ANN__NETWORK_H
#define ANN__NETWORK_H
#include "idxread/idxread.h"
#include <stddef.h>
#include <stdio.h>


typedef struct network {
    float * biases;
    float * nodes;
    float * weights;
    size_t * nnodes;
    size_t nb;        // network total number of bias values
    size_t ni;        // network total number of input nodes
    size_t nl;        // network total number of layers
    size_t nn;        // network total number of nodes
    size_t no;        // network total number of output nodes
    size_t nw;        // network total number of weight values
} Network;

void ann__network_backprop (Network * network, const float learning_rate);
Network * ann__network_create (const size_t nl, size_t * nnodes);
void ann__network_destroy (Network * network);
void ann__network_fwdpass (Network * network);
void ann__network_populate_biases (Network * network);
void ann__network_populate_input (Network * network, const Meta * meta, const float * data, const size_t iobj);
void ann__network_populate_weights (Network * network);
void ann__network_print(FILE * stream, Network * network);

#endif
