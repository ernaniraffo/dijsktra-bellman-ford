// ------------------------------
// Ernani Raffo
// GraphTest.c
// Testing module for Graph ADT
// ------------------------------

#include <stdio.h>
#include "Graph.h"
#include "PriorityQueue.h"

int main(int argc, char** argv) {

    int n = 5;

    printf("Making new Graph...\n");
    Graph G = newGraph(n);
    printf("Order of G: %d\n", getOrder(G));

    printf("adding edges...\n\n");
    printf("1 -> 2: 5.0\n");
    addDirectedEdge(G, 1, 2, 5.0);
    printf("1 -> 4: 6.0\n");
    addDirectedEdge(G, 1, 4, 6.0);
    printf("1 -> 5: 3.0\n\n");
    addDirectedEdge(G, 1, 5, 3.0);

    printf("2 -> 1: 12.0\n\n");
    addDirectedEdge(G, 2, 1, 12.0);
    
    printf("3 -> 2: 2.0\n");
    addDirectedEdge(G, 3, 2, 2.0);
    printf("3 -> 5: 1.0\n\n");
    addDirectedEdge(G, 3, 5, 1.0);

    printf("4 -> 2: 3.6\n");
    addDirectedEdge(G, 4, 2, 3.6);
    printf("4 -> 5: 9.0\n\n");
    addDirectedEdge(G, 4, 5, 9.0);

    printf("5 -> 2: 6.0\n");
    addDirectedEdge(G, 5, 2, 6.0);
    printf("5 -> 3: 2.0\n");
    addDirectedEdge(G, 5, 3, 2.0);
    printf("5 -> 4: 11.0\n\n");
    addDirectedEdge(G, 5, 4, 11.0);

    printf("Graph G:\n");
    printGraph(stdout, G);
    printf("\n");

    printf("Dijkstra with source 1...\n");
    Dijkstra(G, 1);
    printf("\n");

    List P = newList(); // path
    for (int i = 1; i <= getOrder(G); i += 1) {
        printf("distance[%d]: %.0f\n", i, getDistance(G, i));
        getPath(G, getSource(G), i, P);
        printf("Path from source %d to %d: ", getSource(G), i);
        printList(stdout, P);
        clear(P);
        printf("\n");
    }
    printf("\n");

    printf("Is source 1? %s\n\n", getSource(G) == 1 ? "true" : "false");
    printf("Graph G:\n");
    printGraph(stdout, G);
    printf("\n");

    printf("Making new Graph C...\n");
    Graph C = copyGraph(G);
    printf("Graph C:\n");
    printGraph(stdout, C);

    printf("\n");
    
    printf("adding negative edge...\n");
    printf("1 -> 3: -5\n");
    addDirectedEdge(C, 1, 3, -5);
    printf("C:\n");
    printGraph(stdout, C);
    printf("\n");
    
    printf("BellmanFord with source 1\n");
    BellmanFord(C, 1);
    printf("\n");

    P = newList(); // path
    for (int i = 1; i <= getOrder(C); i += 1) {
        printf("distance[%d]: %.0f\n", i, getDistance(C, i));
        getPath(C, getSource(C), i, P);
        printf("Path from source %d to %d: ", getSource(C), i);
        printList(stdout, P);
        clear(P);
        printf("\n");
    }

    printf("Freeing...\n");
    freeList(&P);
    freeGraph(&G);
    freeGraph(&C);
    return 0;
}
