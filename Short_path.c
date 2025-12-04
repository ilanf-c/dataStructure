#include "Short_path.h"
#include "util.h"

typedef struct vertex{
    int s;
    int e;
} vertex;

void dijkstra_pq(int **gp, int start, Priority_queue *pq, int *dist, int* visited, int n){
    dist[start] = 0;
    int *s = malloc(sizeof(*s));
    *s = start;
    pq_push(pq, s);
    while(!pq_isEmpty(pq)){
        int *u = pq_pop(pq);
        if (visited[*u]) continue;
        visited[*u] = 1;
        for(int v = 0; v<n; ++v){
            if (gp[*u][v] != MAX_INT && gp[*u][v]+dist[*u] < dist[v]){
                dist[v] = gp[*u][v] + dist[*u];
                int *t = malloc(sizeof(*t));
                *t = v;
                pq_push(pq, t);
            }
        }
        free(u);
    }
}

void floyd(int **dist, int n){
    for(int k = 0; k<n; ++k){
        for(int i = 0; i<n; ++i){
            for(int j = 0; j<n; ++j){
                if (dist[i][k] != MAX_INT && dist[k][j] != MAX_INT) {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}