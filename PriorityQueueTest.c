// ------------------------------------
// Ernani Raffo
// PriorityQueueTest.c
// Test module for Priority Queue ADT
// -------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"


int main(int argc, char** argv) {

    int n = 10;
    double* keys = (double*) calloc(n, sizeof(double));

    for (double i = 1; i <= n; i += 1) {
        keys[ (int) i ] = i;
    }
    
    PriorityQueue Q = newPriorityQueue(n, keys);
    printPriorityQueue(stdout, Q);

    deleteMin(Q);
    printPriorityQueue(stdout, Q);

    printf("min: %d\n", getMin(Q));

    printf("%d\n", inQueue(Q, 1));

    free(keys);
    freePriorityQueue(&Q);

    return 0;
}
