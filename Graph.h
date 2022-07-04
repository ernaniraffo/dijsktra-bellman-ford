// ---------------------------
// Ernani Raffo
// Graph.h
// Header file for Graph ADT
// ---------------------------

#pragma once

#include "List.h"

#define NIL 0
#define INF 100000001

// Exported Graph type
typedef struct GraphObj* Graph;

// Constructors and Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access Functions
int getOrder(Graph G);
int getParent(Graph G, int u);
double getDistance(Graph G, int u);
int getSource(Graph G);
void getPath(Graph G, int s, int u, List P);

// Manipulation Procedures
void addDirectedEdge(Graph G, int u, int v, double w);
void Dijkstra(Graph G, int s);
int BellmanFord(Graph G, int s);

// Other functions
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
