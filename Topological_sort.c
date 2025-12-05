#include "Topological_sort.h"
#include "stdlib.h"
int topological_sort(int **gp, int *degree, int n){
    int *q = malloc(sizeof(int)*n); // queue
    int top = -1; // queue top pointer
    for(int i = 0; i<n; ++i){
        if (degree[i] == 0){
            q[++top] = i;
        }
    }
    int topo_size = 0;
    while(top != -1){
        int v = q[top--];
        for(int i = 0; i<n; ++i){
            if (gp[v][i]){
                degree[i]--;
                if (degree[i] == 0){
                    q[++top] = i;
                }
            }
        }
        ++topo_size;
    }
    if (topo_size < n){
        return 0; // topo failed -- ring
    }
    return 1;
}