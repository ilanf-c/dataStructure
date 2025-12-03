#include "InOrderThreadBinTree.h"

void InOrderVisit(ThreadNode *node, ThreadNode **pre) {
  if (!node) return ;
  if (!node->lchild){
    node->ltag = 1;
    node->lchild = *pre;
  }
  if((*pre) && !(*pre)->rchild){
    (*pre)->rtag = 1;
    (*pre)->rchild = node;
  }
  *pre = node;
}

void InOrderThreading(ThreadNode *T, ThreadNode **pre){
  if(!T) return ;
  InOrderThreading(T->lchild, pre);
  InOrderVisit(T, pre);
  InOrderThreading(T->rchild, pre);
}

ThreadTree CreateInOrderThreadedTree(ThreadTree T) {
  ThreadNode *pre = NULL;
  InOrderThreading(T, &pre);
  if (pre && !pre->rchild) {
    pre->rtag = 1;
    pre->rchild = NULL;
  }
  return T;
}

ThreadNode *InOrderFindLast(ThreadNode *node) {
  if(node->ltag == 1){
    return node->lchild;
  } else {
    // go to the rightmost child of the left subtree
    ThreadNode *cur = node->lchild;
    while(cur && cur->rtag == 0){
      cur = cur->rchild;
    }
    return cur;
  }
}

ThreadNode *InOrderFindNext(ThreadNode *node){
  if (node->rtag == 1){
    return node->rchild;
  }else{
    // go to the leftmost child of the right subtree
    ThreadNode *cur = node->rchild;
    while(cur && cur->ltag == 0){
      cur = cur->lchild;
    }
    return cur;
  }
}


void InOrderTraverse(ThreadNode *T){
  if(!T) return ;
  InOrderTraverse(T->lchild);
  Visit(T);
  InOrderTraverse(T->rchild);
}
