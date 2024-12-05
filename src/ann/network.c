#include "ann/network.h"
#include "ann/afuns.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"


size_t calc_nb (const size_t nl, const size_t * nnodes);
size_t calc_ni (const size_t nl, const size_t * nnodes);
size_t calc_nn (const size_t nl, const size_t * nnodes);
size_t calc_no (const size_t nl, const size_t * nnodes);
size_t calc_nw (const size_t nl, const size_t * nnodes);


void ann__network_backprop (Network * network, const float learning_rate) {
}


Network * ann__network_create (const size_t nl, size_t * nnodes) {
    Network * network = calloc(1, sizeof (Network));
    if (network == nullptr) {
        fprintf(stderr, "Something went wrong allocating memory for 'Network'. Aborting.\n");
        exit(EXIT_FAILURE);
    }
    network->nnodes = nnodes;
    network->nl = nl;
    network->nn = calc_nn(nl, nnodes);
    network->ni = calc_ni(nl, nnodes);
    network->no = calc_no(nl, nnodes);
    network->nw = calc_nw(nl, nnodes);
    network->nb = calc_nb(nl, nnodes);
    network->nodes = calloc(network->nn, sizeof(float));
    if (network->nodes == nullptr) {
        fprintf(stderr, "Something went wrong allocating memory for 'Network' member 'nodes'. Aborting.\n");
        exit(EXIT_FAILURE);
    }
    network->biases = calloc(network->nb, sizeof(float));
    if (network->biases == nullptr) {
        fprintf(stderr, "Something went wrong allocating memory for 'Network' member 'biases'. Aborting.\n");
        exit(EXIT_FAILURE);
    }
    network->weights = calloc(network->nw, sizeof(float));
    if (network->weights == nullptr) {
        fprintf(stderr, "Something went wrong allocating memory for 'Network' member 'weights'. Aborting.\n");
        exit(EXIT_FAILURE);
    }
    return network;
}


void ann__network_fwdpass (Network * network) {
    size_t nl = network->nl;
    float * w = &network->weights[0];
    float * b = &network->biases[0];
    float * in = &network->nodes[0];
    float * out = in + network->nnodes[0];
    for (size_t il = 0; il < nl - 1; il++) {
        size_t inr = network->nnodes[il];
        size_t onr = network->nnodes[il+1];
        for (size_t i = 0; i < onr; i++) {
            *out = 0;
            for (size_t j = 0; j < inr; j++) {
                *out += *w * *in;          // apply weight
                w++;
                in++;
            }
            *out += *b;                    // apply bias
            *out = ann__afuns_relu(*out);  // apply activation function
            out++;
            b++;
            if (i < onr - 1) {
                in -= inr;
            }
        }
    }
}


void ann__network_destroy (Network * network) {
    free(network->nodes);
    network->nodes = nullptr;
    free(network->biases);
    network->biases = nullptr;
    free(network->weights);
    network->weights = nullptr;
    free(network);
    network = nullptr;
}


void ann__network_print(FILE * stream, Network * network) {
    fprintf(stream, "network layout\n");
    fprintf(stream, "- nodes: %zu\n", network->nn);
    fprintf(stream, "- layers: %zu\n", network->nl);
    fprintf(stream, "- input nodes: %zu\n", network->ni);
    fprintf(stream, "- hidden nodes: %zu\n", network->nn - network->ni - network->no);
    fprintf(stream, "- output nodes: %zu\n", network->no);
    fprintf(stream, "- weights: %zu\n", network->nw);
    fprintf(stream, "- biases: %zu\n", network->nb);
}


void ann__network_populate_biases (Network * network) {
    size_t nb = network->nb;
    for (size_t i = 0; i < nb; i++) {
        int z = rand() % 200 - 100;
        network->biases[i] = (float) z / 100;
    }
}


void ann__network_populate_input (Network * network, const Meta * meta, const float * data, const size_t iobj) {
    size_t ni = network->ni;
    for (size_t i = 0; i < ni; i++) {
        size_t j = iobj * meta->stride + i;
        network->nodes[i] = data[j];
    }
}


void ann__network_populate_weights (Network * network) {
    size_t nw = network->nw;
    for (size_t i = 0; i < nw; i++) {
        int z = rand() % 200 - 100;
        network->weights[i] = (float) z / 100;
    }
}


size_t calc_nb (const size_t nl, const size_t * nnodes) {
    size_t n = 0;
    for (size_t i = 1; i < nl; i++) {
        n += nnodes[i];
    }
    return n;
}


size_t calc_ni (const size_t, const size_t * nnodes) {
    return nnodes[0];
}


size_t calc_nn (const size_t nl, const size_t * nnodes) {
    size_t n = 0;
    for (size_t i = 0; i < nl; i++) {
        n += nnodes[i];
    }
    return n;
}


size_t calc_no (const size_t nl, const size_t * nnodes) {
    return nnodes[nl - 1];
}


size_t calc_nw (const size_t nl, const size_t * nnodes) {
    size_t n = 0;
    for (size_t i = 0; i < nl - 1; i++) {
        n += nnodes[i] * nnodes[i+1];
    }
    return n;
}
