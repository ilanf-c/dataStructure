#include "Short_path.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* comparator for pq that orders node indices by current distance array */
static int *gdist_for_pq = NULL;
static int node_cmp(const void *a, const void *b){
    const int ia = *(const int*)a;
    const int ib = *(const int*)b;
    int da = gdist_for_pq[ia];
    int db = gdist_for_pq[ib];
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

/* helper to allocate an n x n adjacency matrix and fill with MAX_INT */
static int **alloc_graph(int n){
    int **gp = malloc(sizeof(int*) * n);
    if (!gp) return NULL;
    for(int i = 0; i < n; ++i){
        gp[i] = malloc(sizeof(int) * n);
        for(int j = 0; j < n; ++j) gp[i][j] = (i==j) ? 0 : MAX_INT;
    }
    return gp;
}

static void free_graph(int **gp, int n){
    for(int i = 0; i < n; ++i) free(gp[i]);
    free(gp);
}

int testShortPath(){
    printf("\n**TEST[testShortPath]**\n");
    int n = 4;
    int **gp = alloc_graph(n);
    if (!gp) return 1;

    /* undirected weighted graph
       0--1 (1)
       0--2 (4)
       1--2 (2)
       1--3 (5)
       2--3 (1)
    */
    gp[0][1] = gp[1][0] = 1;
    gp[0][2] = gp[2][0] = 4;
    gp[1][2] = gp[2][1] = 2;
    gp[1][3] = gp[3][1] = 5;
    gp[2][3] = gp[3][2] = 1;

    /* Dijkstra test */
    int *dist = malloc(sizeof(int) * n);
    int *visited = malloc(sizeof(int) * n);
    for(int i = 0; i < n; ++i){ dist[i] = MAX_INT; visited[i] = 0; }

    gdist_for_pq = dist;
    Priority_queue *pq = pq_create(node_cmp, 0);
    if (!pq) { free_graph(gp,n); free(dist); free(visited); return 1; }

    dijkstra_pq(gp, 0, pq, dist, visited, n);

    int expected0[] = {0,1,3,4};
    int dijkstra_ok = 1;
    for(int i = 0; i < n; ++i){
        if (dist[i] != expected0[i]) { dijkstra_ok = 0; break; }
    }

    /* cleanup pq's internal items (pq_free will free remaining items) */
    pq_free(pq, free);

    printf("Dijkstra distances: ");
    for(int i=0;i<n;++i) printf("%d ", dist[i]);
    printf("\n");

    /* Floyd test */
    int **dist2 = alloc_graph(n);
    if (!dist2) { free_graph(gp,n); free(dist); free(visited); return 1; }
    /* copy gp into dist2 (floyd will update dist2) */
    for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) dist2[i][j] = gp[i][j];

    floyd(dist2, n);

    int expected_all[4][4] = {
        {0,1,3,4},
        {1,0,2,3},
        {3,2,0,1},
        {4,3,1,0}
    };
    int floyd_ok = 1;
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) if (dist2[i][j] != expected_all[i][j]) floyd_ok = 0;

    printf("Floyd distances:\n");
    for(int i=0;i<n;++i){ for(int j=0;j<n;++j) printf("%d ", dist2[i][j]); printf("\n"); }

    int res = 0;
    if (!dijkstra_ok) {
        fprintf(stderr, "Dijkstra test failed\n"); res = 1;
    }
    if (!floyd_ok) {
        fprintf(stderr, "Floyd test failed\n"); res = 1;
    }

    free_graph(gp, n);
    free_graph(dist2, n);
    free(dist);
    free(visited);
    printf("Shortest Path tests passed\n");
    return res;
}