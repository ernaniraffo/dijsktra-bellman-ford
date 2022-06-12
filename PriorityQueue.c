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
    int length;
} PriorityQueueObj;

// Helper functions
int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return (2 * i) + 1;
}

void swap(int* myArray, int i, int j) {

    int temp = myArray[i];
    myArray[i] = myArray[j];
    myArray[j] = temp;

    return;
}

void heapify(PriorityQueue Q, i) {

    int l = left(i);
    int r = right(i);
    int smallest;

    if (l <= Q->heapSize && Q->key[Q->A[l]] < Q->key[Q->A[i]]) {
        smallest = l;
    } else {
        smallest = i;
    }
    if (r <= Q->heapSize && Q->key[Q->A[r]] < Q->key[Q->A[smallest]]) {
        smallest = r;
    }

    if (smallest != i) {
        swap(Q->A, i, smallest);
        heapify(Q, smallest);
    }
    
    return;
}

void buildHeap(PriorityQueue Q) {
    
    for (int i = Q->heapSize / 2; i >= 1; i--) {
        heapify(Q, i);
    }
    return;
}

// Constuctors and Destructors

PriorityQueue newPriorityQueue(int n, double* key) {
    PriorityQueue Q = malloc(sizeof(PriorityQueueObj));
    
    Q->A = (int*) calloc(n, sizeof(int));
    for (int i = 1; i <= n; i++) {
        A[i] = i;
    }

    Q->I = (int*) calloc(n, sizeof(int));
    for (int i = 1; i <= n; i++) {
        I[i] = i;
    }

    Q->key = key;
    Q->length = n;
    Q->heapSize = n;
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

// Access Functions

int getNumElements(PriorityQueue Q) {
    return Q->heapSize;
}

int getMin(PriorityQueue Q) {
    if (getNumElements(Q) < 1) {
        fprintf(stderr, "Error: PriorityQueue: getMin(): no elements in Queue\n");
        exit(EXIT_FAILURE);
    }
    return Q->A[1];
}

int inQueue(PriorityQueue Q, int u) {
    return (Q->I[u] >= 1 && Q->I[u] <= Q->heapSize);
}

// Manipulation Procedures

void deleteMin(PriorityQueue Q) {
    if (getNumElements(Q) < 1) {
        fprintf(stderr, "Error: PriorityQueue: deleteMin(): no elements in Queue\n");
        exit(EXIT_FAILURE);
    }

    int min = Q->A[1];

    Q->A[1] = Q->A[Q->heapSize];
    Q->heapSize -= 1;
    heapify(Q, 1);

    return;
}

void decreaseKey(PriorityQueue Q, int u, double k) {
    if (!inQueue(Q, u)) {
        fprintf(stderr, "Error: PriorityQueue: decreasekey(): element not in Queue\n");
        exit(EXIT_FAILURE);
    }
    if (k < Q->key[u]) {
        Q->key[u] = k;
    }
    return;
}
