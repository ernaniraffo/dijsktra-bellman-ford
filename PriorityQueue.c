// ---------------------------------------------
// Ernani Raffo
// PriorityQueue.c
// Implementation file for Priority Queue ADT
// ---------------------------------------------

#include <stdio.h>
#include "PriorityQueue.h"

// Private PriorityQueue struct
typedef struct PriorityQueueObj {
    int* A;
    int* I;
    double* key;
    int heapSize;
} PriorityQueueObj;

// Constuctors and Destructors

PriorityQueue newPriorityQueue(int n, double* key) {
    PriorityQueue Q = malloc(sizeof(PriorityQueueObj));
    Q->A = (int*) calloc(n, sizeof(int));
    Q->I = (int*) calloc(n, sizeof(int));
    Q->key = key;
    Q->heapSize = 0;
    return Q;
}

void freePriorityQueue(PriorityQueue* pQ) {
    if (pQ != NULL && *pQ != NULL) {
        free((*pQ)->A);
        free((*pQ)->I);
        free(*pQ);
        *pQ = NULL;
    }
    return;
}


