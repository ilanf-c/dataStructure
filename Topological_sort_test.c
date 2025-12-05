#include "Topological_sort.h"
#include <stdio.h>
#include <stdlib.h>

/* allocate an n x n zero-initialized adjacency matrix */
static int **alloc_graph(int n) {
    int **gp = malloc(sizeof(int *) * n);
    if (!gp) return NULL;
    for (int i = 0; i < n; ++i) {
        gp[i] = calloc(n, sizeof(int));
        if (!gp[i]) return NULL;
    }
    return gp;
}

static void free_graph(int **gp, int n) {
    for (int i = 0; i < n; ++i) free(gp[i]);
    free(gp);
}

/* add a directed edge u -> v and bump v's indegree */
static void add_edge(int **gp, int *degree, int u, int v) {
    gp[u][v] = 1;
    degree[v]++;
}

int testTopo() {
    printf("\n**TEST[testTopo]**\n");
    int res = 0;

    /* Acyclic graph */
    int n = 6;
    int **gp = alloc_graph(n);
    int *degree = calloc(n, sizeof(int));
    if (!gp || !degree) return 1;

    /* edges: 0->1,0->2,1->3,2->3,3->4,2->5 */
    add_edge(gp, degree, 0, 1);
    add_edge(gp, degree, 0, 2);
    add_edge(gp, degree, 1, 3);
    add_edge(gp, degree, 2, 3);
    add_edge(gp, degree, 3, 4);
    add_edge(gp, degree, 2, 5);

    int ok_dag = topological_sort(gp, degree, n);
    int degrees_zero = 1;
    for (int i = 0; i < n; ++i) {
        if (degree[i] != 0) { degrees_zero = 0; break; }
    }
    printf("DAG result: %d, degrees_zero: %d\n", ok_dag, degrees_zero);
    if (!(ok_dag && degrees_zero)) {
        fprintf(stderr, "Topological sort failed on DAG\n");
        res = 1;
    }

    free_graph(gp, n);
    free(degree);

    /* Cyclic graph */
    int n2 = 3;
    int **gp2 = alloc_graph(n2);
    int *degree2 = calloc(n2, sizeof(int));
    if (!gp2 || !degree2) return 1;

    /* cycle: 0->1->2->0 */
    add_edge(gp2, degree2, 0, 1);
    add_edge(gp2, degree2, 1, 2);
    add_edge(gp2, degree2, 2, 0);

    int ok_cycle = topological_sort(gp2, degree2, n2);
    printf("Cycle result: %d\n", ok_cycle);
    if (ok_cycle != 0) {
        fprintf(stderr, "Topological sort should fail on cycle\n");
        res = 1;
    }

    free_graph(gp2, n2);
    free(degree2);

    if (res == 0) printf("Topological sort tests passed\n");
    return res;
}