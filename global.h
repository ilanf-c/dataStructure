#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct ThreadNode{
  struct ThreadNode *lchild, *rchild;
  char data;
  int ltag, rtag; // 0 for child, 1 for thread
} ThreadNode, *ThreadTree;

typedef int (*pq_cmp)(const void *a, const void *b) ;
typedef struct Priority_queue{
    void **data;
    int size;
    int capacity;
    pq_cmp cmp;
} Priority_queue;

typedef int* dsu;

#endif