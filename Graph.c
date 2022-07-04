// -----------------------------------
// Ernani Raffo
// Graph.c
// Implementation file for Graph ADT
// -----------------------------------

#include <stdlib.h>
#include "List.h"
#include "Graph.h"
#include "PriorityQueue.h"

// Private GraphObj type
typedef struct GraphObj {
    int* parent;
    double* distance;
    double** weight;
    List* adj;
    int order;
    int source;
} GraphObj;

// Constructors and Destructors

// newGraph()
// Creates and returns new Graph object
Graph newGraph(int n) {
    
    Graph G = malloc(sizeof(Graph));
    G->parent = calloc(n + 1, sizeof(int));
    G->distance = calloc(n + 1, sizeof(double));
    G->weight = calloc(n + 1, sizeof(double*));
    G->adj = calloc(n + 1, sizeof(List));
    
    for (int i = 1; i <= n; i += 1) {

        G->adj[i] = newList();

        for (int j = 1; j <= n; j += 1) {
            G->weight[i][j] = INF;
        }

    }

    G->order = n;
    G->source = NIL;
    
    return G;
}

// freeGraph()
// Frees heap memory pointed to *pG
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {

        for (int i = 1; i <= getOrder(*pG); i += 1) {
            freeList(&(*pG)->adj[i]);
        }

        free((*pG)->weight);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
    return;
}

// Access Functions

// getOrder()
// Returns the order of G
int getOrder(Graph G) {
    if (G == NULL) {
        printf("Graph error: calling getOrder() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

// getParent()
// Returns the parent of u
int getParent(Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: calling getParent() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

// getDistance()
// Returns the distance from the source vertex to u
double getDistance(Graph G, int u) {
    if (G == NULL) {
        printf("Graph error: calling getDistance() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->distance[u];
}

// getSource()
// Returns the source vertex of Graph G
int getSource(Graph G) {
    if (G == NULL) {
        printf("Graph error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return G->source;
}

// getPath()
// Returns the path from the source to vertex to u
// Pre: isEmpty(P), getSource(G) == s
void getPath(Graph G, int s, int u, List P) {
    if (G == NULL) {
        printf("Graph error: calling getPath() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(P) != 0) {
        printf("Graph error: calling getPath() with non-empty List\n");
        exit(EXIT_FAILURE);
    }
    if (getSource(G) != s) {
        printf("Graph error: calling getPath() with wrong source vertex\n");
        exit(EXIT_FAILURE);
    }

    if (getDistance(G, u) != INF) {
        if (u == G->source) {
            append(P, u);
        } else {
            getPath(G, s, G->parent[u], P);
            append(P, u);
        }
        return;
    }
    append(P, NIL);
    return;
}

// Manipulation Procedures

// addDirectedEdge
// Adds v to the adjacency list of u, and sets the
// u'th row, v'th column of the weight array w
void addDirectedEdge(Graph G, int u, int v, double w) {
    if (G == NULL) {
        printf("Graph error: calling addDirectedEdge() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    List L = G->adj[u];

    if (length(L) > 0) {
        moveFront(L);
    }

    while (1) {
        if (index(L) < 0) { // higher than any number in List (if any)
            append(L, v);
            return;
        } else if (v <= get(L)) { // can not go higher in list
            insertBefore(L, v);
            return;
        } else if (v > get(L)) { // can go higher in list
            moveNext(L);
        }
    }

    G->weight[u][v] = w;

    return;
}

void Initialize(Graph G, int s) {
    for (int x = 1; x <= getOrder(G); x += 1) {
        G->distance[x] = INF;
        G->parent[x] = NIL;
    }
    G->distance[s] = 0;
    return;
}

// Relax1()
// Relaxes edges in a weighted graph.
// Used by Dijkstra()
void Relax1(Graph G, int u, int v, PriorityQueue Q) {
    
    int distanceU = G->distance[u];
    int weightUV = G->weight[u][v];

    int total = (distanceU == INF) || (weightUV == INF) ? INF : distanceU + weightUV;

    if (G->distance[v] > total) {
        decreaseKey(Q, v, total);
        G->parent[v] = u;
    }

    return;
}

// Relax2()
// Relaxes edges in a weighted graph.
// Used by BellmanFord()
void Relax2(Graph G, int u, int v) {

    int distanceU = G->distance[u];
    int weightUV = G->weight[u][v];

    int total = (distanceU == INF) || (weightUV == INF) ? INF : distanceU + weightUV;

    if (G->distance[v] > total) {
        G->distance[v] = total;
        G->parent[v] = u;
    }

    return;
}

// Dijkstra()
// Peforms Dijsktra's algorithm with source s
void Dijkstra(Graph G, int s) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling Dijkstra() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (s < 1 || s > getOrder(G)) {
        fprintf(stderr, "Graph error: calling Dijkstra() with an out of range source vertex\n");
        exit(EXIT_FAILURE);
    }
    
    Initialize(G, s);
    PriorityQueue Q = newPriorityQueue(G->order, G->distance);

    while (getNumElements(Q) != 0) {
        int u = getMin(Q);
        for (moveFront(G->adj[u]); index(G->adj[u]); moveNext(G->adj[u])) {
            int v = get(G->adj[u]);
            Relax1(G, u, v, Q);
        }
    }
    
    return;
}

// BellmanFord()
// Performs Bellman-Ford's algorithm with a source s
int BellmanFord(Graph G, int s) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling BellmanFord() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (s < 1 || s > getOrder(G)) {
        fprintf(stderr, "Graph error: calling BellmanFord() with an out of range source vertex\n");
        exit(EXIT_FAILURE);
    }

    Initialize(G, s);
    int n = getOrder(G);

    for (int i = 1; i <= (n - 1); i += 1) {
        for (int x = 1; x <= n; x += 1) {
            for (moveFront(G->adj[x]); index(G->adj[x]) >= 0; moveNext(G->adj[x])) {
                Relax2(G, x, get(G->adj[x]));
            }
        }
    }

    for (int x = 1; x <= n; x += 1) {
        for (moveFront(G->adj[x]); index(G->adj[x]) >= 0; moveNext(G->adj[x])) {
            int y = get(G->adj[x]);
            printf("BellmanFord(): G->distance[y]: %.0lf\n", G->distance[y]);
            printf("BellmanFord(): G->distance[x] + G->weight[x][y]: %.0lf\n", G->distance[x] + G->weight[x][y]);
            if (G->distance[y] > G->distance[x] + G->weight[x][y]) {
                printf("Negative cycle detected\n");
                return false;
            }
        }
    }

    return true;
}


// Other functions

// copyGraph()
// Returns a copy of Graph G.
Graph copyGraph(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling copyGraph() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    Graph C = newGraph(G->order);
    
    for (int i = 1; i <= getOrder(C); i += 1) {
        C->parent[i] = NIL;
        C->distance[i] = INF;

        for (moveFront(G->adj[i]); index(G->adj[i]); moveNext(G->adj[i])) {
            int v = get(G->adj[i]);
            addDirectedEdge(C, i, v, G->weight[i][v]);
        }

    }

    return C;
}

// printGraph()
// Prints the ajacency list representation of Graph G
void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph error: calling printGraph() on a NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= getOrder(G); i += 1) {
        fprintf(out, "%d: ", i);
        for (moveFront(G->adj[i]); index(G->adj[i]); moveNext(G->adj[i])) {
            fprintf(out, "(%d, %.1lf) ", i, G->weight[i][get(G->adj[i])]);
        }
        printf("\n");
    }

    return;
}
