// ---------------------------------
// Ernani Raffo
// PrioriyQueue.h
// Header file for PriorityQueue.h
// ---------------------------------

#pragma once

#include <stdio.h>
#include <stdlib.h> 

// Exported PriorityQueue type
typedef struct PriorityQueueObj* PriorityQueue;

// Constructors and Destructors
PriorityQueue newPriorityQueue(int n, double* key);
void freePriorityQueue(PriorityQueue* pQ);

// Access Functions
int getNumElements(PriorityQueue Q);
int getMin(PriorityQueue Q);
int inQueue(PriorityQueue Q, int u);

// Manipulation Procedures
void deleteMin(PriorityQueue Q);
void decreaseKey(PriorityQueue Q, int u, double k);

// Other functions
void printPriorityQueue(FILE* out, PriorityQueue Q);
