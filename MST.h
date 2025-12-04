#ifndef _MST_H_
#define _MST_H_
#include "global.h"
#define MAX_INT 0x01111111
int kuskal(int **gp, Priority_queue *pq, dsu p, int n);
int prim(int **gp, int start, int *visited, int *low_cost, int n);

#endif