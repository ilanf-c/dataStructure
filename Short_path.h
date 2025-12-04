#ifndef _SHORT_PATH_
#define _SHORT_PATH_
#include "global.h"
#define MAX_INT 0x01111111
void dijkstra_pq(int **gp, int start, Priority_queue *pq, int *dist, int *visited, int n);
void floyd(int **dist, int n);

#endif