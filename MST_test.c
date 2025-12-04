#include "MST.h"
#include "util.h"
#include "global.h"

/* comparator for edge-like structs: layout must match MST's edge allocation */
struct edge_like { int s; int e; int w; };
static int edge_cmp(const void *a, const void *b) {
    const struct edge_like *ea = a;
    const struct edge_like *eb = b;
    return (ea->w < eb->w) ? -1 : (ea->w > eb->w) ? 1 : 0;
}

int testMST(){
    printf("\n**TEST[testMST]**\n");
    /* Example graph (4 nodes)
       edges:
       0-1:1, 0-2:3, 0-3:4, 1-2:2, 1-3:5, 2-3:6
       MST weight = 1 + 2 + 4 = 7
    */
    int n = 4;
    int expected = 7;
    int **gp = malloc(sizeof(int*) * n);
    if (!gp) return 1;
    for (int i = 0; i < n; ++i) {
        gp[i] = calloc(n, sizeof(int));
        if (!gp[i]) return 1;
    }
    gp[0][1] = gp[1][0] = 1;
    gp[0][2] = gp[2][0] = 3;
    gp[0][3] = gp[3][0] = 4;
    gp[1][2] = gp[2][1] = 2;
    gp[1][3] = gp[3][1] = 5;
    gp[2][3] = gp[3][2] = 6;

    /* Run Prim */
    int *visited = malloc(sizeof(int) * n);
    int *low_cost = malloc(sizeof(int) * n);
    if (!visited || !low_cost) return 1;
    for(int i = 0; i<n; ++i) visited[i] = 0;
    for(int i = 0; i<n; ++i) low_cost[i] = MAX_INT;
    int prim_res = prim(gp, 0, visited, low_cost, n);

    /* Run Kruskal: need PQ and DSU */
    Priority_queue *pq = pq_create(edge_cmp, 0);
    if (!pq) return 1;
    dsu p = dsu_create(n);
    if (!p) { pq_free(pq, NULL); return 1; }
    int kruskal_res = kuskal(gp, pq, p, n);

    /* cleanup */
    pq_free(pq, NULL);
    dsu_free(p);
    for (int i = 0; i < n; ++i) free(gp[i]);
    free(gp);
    free(visited);
    free(low_cost);

    printf("prim_res=%d kruskal_res=%d expected=%d\n", prim_res, kruskal_res, expected);
    if (prim_res == expected && kruskal_res == expected) {
        printf("MST tests passed\n");
        return 0;
    } else {
        fprintf(stderr, "MST tests failed\n");
        return 1;
    }
}
