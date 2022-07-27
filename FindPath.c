// ------------------------
// Ernani Raffo
// FindPath.c
// ------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char** argv) {

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <infile> <outfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *in, *out;

    in = fopen(argv[1], "r");
    if (!in) {
        fprintf(stderr, "Error: could not open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    out = fopen(argv[2], "w");
    if (!out) {
        fprintf(stderr, "Error could not open %s\n", argv[2]);
        fclose(in);
        exit(EXIT_FAILURE);
    }

    int n, u, v, w;
    bool negativeEdgeWeight = false;

    fscanf(in, "%d", &n);

    Graph G = newGraph(n);

    while (fscanf(in, "%d %d %d", &u, &v, &w) != EOF) {
        if (u == 0 & v == 0 & w == 0) {
            break;
        }
        if (w < 0) {
            negativeEdgeWeight = true;
        }
        addDirectedEdge(G, u, v, w);
    }

    printGraph(out, G);
    fprintf(out, "\n");

    int s;
    double d;
    List P = newList(); // path

    while (fscanf(in, "%d %d", &s, &u) != EOF) {
        if (s == 0 & u == 0) {
            break;
        }
        if (negativeEdgeWeight) {
            if (BellmanFord(G, s)) {
                d = getDistance(G, u);
                if (d < INF) {
                    getPath(G, s, u, P);
                    fprintf(out, "A shortest path from %d to %d of length %.1lf is: ", s, u, d);
                    printList(out, P);
                    fprintf(out, "\n");
                    clear(P);
                } else {
                    fprintf(out, "No path from %d to %d exists\n", s, u);
                }
            } else {
                fprintf(out, "The SSSG problem is not solvable from source %d\n", s);
            }
        } else {
            Dijkstra(G, s);
            d = getDistance(G, u);
            if (d < INF) {
                getPath(G, s, u, P);
                fprintf(out, "A shortest path from %d to %d of length %.1lf is: ", s, u, d);
                printList(out, P);
                clear(P);
            } else {
                fprintf(out, "No path from %d to %d exists\n", s, u);
            }
        }
    }

    fclose(in);
    fclose(out);
    freeGraph(&G);
    freeList(&P);
    return 0;
}
