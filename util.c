#include "util.h"
#include "global.h"
#include <stdlib.h>

void Visit(ThreadNode *node) {
  if (node) {
    printf("%c ", node->data);
  }
}

static void swap_ptr(void **a, void **b){
  void *t = *a; *a = *b; *b = t;
}

Priority_queue *pq_create(pq_cmp cmp, int capacity){
  if (!cmp) return NULL;
  if (capacity == 0) capacity = 16;
  Priority_queue *pq = (Priority_queue*)malloc(sizeof(*pq));
  if (!pq) return NULL;
  pq->data = (void*)malloc(sizeof(void*) * capacity);
  if (!pq->data) {free(pq); return NULL;}
  pq->size = 0;
  pq->capacity = capacity;
  pq->cmp = cmp;
  return pq;
}

void pq_free(Priority_queue *pq, void (*free_item)(void *)){
  if (!pq) return ;
  if (free_item) {
    for(int i = 0; i<pq->size; ++i)
      free_item(pq->data[i]);
  }
  free(pq->data);
  free(pq);
}

int pq_isEmpty(const Priority_queue *pq){ return pq ? (pq->size==0) : 1;}
int pq_size(const Priority_queue *pq){ return pq ? pq->size : 0;}
void *pq_top(const Priority_queue*pq){ return (pq_isEmpty(pq)) ? NULL : pq->data[0];}

static int ensure_capacity(Priority_queue *pq, int min_capacity){
  if (pq->capacity >= min_capacity) return 0;
  int newcap = pq->capacity ? pq->capacity*2 : 16;
  while(newcap < min_capacity) newcap <<= 1;
  void **newdata = realloc(pq->data, sizeof(void*) * newcap);
  if (!newdata) return -1;
  pq->data = newdata;
  pq->capacity = newcap;
  return 0;
}

int pq_push(Priority_queue *pq, void *item){
  if (!pq) return -1;
  if (ensure_capacity(pq, pq->size+1) != 0) return -1;
  int i = pq->size++;
  pq->data[i] = item;
  while(i > 0){
    int parent = (i-1) >> 1;
    if (pq->cmp(pq->data[i], pq->data[parent]) >= 0) break;
    swap_ptr(&pq->data[i], &pq->data[parent]);
    i = parent;
  }
  return 0;
}

void *pq_pop(Priority_queue *pq){
  if (!pq || pq->size == 0) return NULL;
  void *ret = pq->data[0];
  pq->size--;
  if (pq->size > 0){
    pq->data[0] = pq->data[pq->size];
    int i = 0;
    while(1) {
      int l = 2*i + 1;
      int r = l + 1;
      int smallest = i;
      if (l < pq->size && pq->cmp(pq->data[l], pq->data[smallest]) < 0) smallest = l;
      if (r < pq->size && pq->cmp(pq->data[r], pq->data[smallest]) < 0) smallest = r;
      if (smallest == i) break;
      swap_ptr(&pq->data[i], &pq->data[smallest]);
      i = smallest;
    }
  }
  return ret;
}

dsu dsu_create(int size){
  if (size <= 0) return NULL;
  dsu parent = malloc(sizeof(int) * size);
  if (!parent) return NULL;
  for(int i = 0; i < size; ++i) parent[i] = -1;
  return parent;
}

void dsu_free(dsu parent){
  free(parent);
}

int dsu_find(dsu parent, int i){
  if (!parent) return -1;
  int root = i;
  while (parent[root] >= 0) root = parent[root];
  while (i != root){
    int next = parent[i];
    parent[i] = root;
    i = next;
  }
  return root;
}

void dsu_union(dsu parent, int i, int j){
  int sum = parent[i] + parent[j];
  if (parent[i] < parent[j]){
    parent[j] = i;
    parent[i] = sum;
  } else{
    parent[i] = j;
    parent[j] = sum;
  }
}