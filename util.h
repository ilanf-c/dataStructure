#ifndef _UTIL_H
#define _UTIL_H
#include "global.h"
void Visit(ThreadNode *node);

// methods for priority queue
Priority_queue *pq_create(pq_cmp cmp, int capacity);
void pq_free(Priority_queue *pq, void (*free_item)(void *));
int pq_push(Priority_queue *pq, void *item);
void *pq_pop(Priority_queue *pq);
void *pq_top(const Priority_queue *pq);
int pq_isEmpty(const Priority_queue *pq);
int pq_size(const Priority_queue *pq);

// methods for union-find set
// `dsu` is typedef'd as `int*` in global.h (array of ints)
dsu dsu_create(int size);
void dsu_free(dsu parent);
int dsu_find(dsu parent, int i);
void dsu_union(dsu parent, int i, int j);


#endif