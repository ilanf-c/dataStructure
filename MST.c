#include "MST.h"
#include "global.h"
#include "util.h"

typedef struct edge{
    int s;
    int e;
    int w;
} edge;

int kuskal(int **gp, Priority_queue *pq, dsu p, int n){
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            if (gp[i][j] == 0) continue;     
            edge *e = malloc(sizeof(*e));
            if (!e) return -1;
            e->s = i; e->e = j; e->w = gp[i][j];
            pq_push(pq, e);
        }
    }
    int min_w_sum = 0;
    int vertex_used = 0;
    while(!pq_isEmpty(pq) && vertex_used < n-1){
        edge *e = pq_pop(pq);
        if (!e) break;
        int i = dsu_find(p, e->s);
        int j = dsu_find(p, e->e);
        if (i != j){
            dsu_union(p, i, j);
            min_w_sum += e->w;
            ++vertex_used;
        }
        free(e);
    }
    return min_w_sum;
}

int prim(int **gp, int start, int *visited, int *low_cost, int n){
    if (start < 0 || start >= n) start = 0;
    low_cost[start] = 0;

    int min_w_sum = 0;
    for (int iter = 0; iter < n; ++iter) {
        int u = -1;
        int best = MAX_INT;
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && low_cost[v] < best) {
                best = low_cost[v];
                u = v;
            }
        }
        if (u == -1) break; /* remaining vertices unreachable */
        visited[u] = 1;
        if (best != MAX_INT) min_w_sum += best;

        /* update neighbors' low_cost */
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && gp[u][v] && gp[u][v] < low_cost[v]) {
                low_cost[v] = gp[u][v];
            }
        }
    }
    return min_w_sum;
}