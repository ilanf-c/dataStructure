#ifndef _UTIL_H
#define _UTIL_H

typedef struct ThreadNode{
  struct ThreadNode *lchild, *rchild;
  char data;
  int ltag, rtag; // 0 for child, 1 for thread
} ThreadNode, *ThreadTree;

void Visit(ThreadNode *node);

#endif