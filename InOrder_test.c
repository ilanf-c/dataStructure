#include "util.h"
#include "InOrderThreadBinTree.h"

#include <stdio.h>
#include <stdlib.h>

int testInOrder(){
  // 7 nodes binary tree
  ThreadNode *A = (ThreadNode *)malloc(sizeof(ThreadNode));
  ThreadNode *B = (ThreadNode *)malloc(sizeof(ThreadNode));
  ThreadNode *C = (ThreadNode *)malloc(sizeof(ThreadNode));
  ThreadNode *D = (ThreadNode *)malloc(sizeof(ThreadNode));
  ThreadNode *E = (ThreadNode *)malloc(sizeof(ThreadNode));
  ThreadNode *F = (ThreadNode *)malloc(sizeof(ThreadNode));
  ThreadNode *G = (ThreadNode *)malloc(sizeof(ThreadNode));
  A->data = 'A'; B->data = 'B'; C->data = 'C'; D->data = 'D';
  E->data = 'E'; F->data = 'F'; G->data = 'G';
  A->lchild = B; A->rchild = C; A->ltag = 0; A->rtag = 0;
  B->lchild = D; B->rchild = E; B->ltag = 0; B->rtag = 0;
  C->lchild = F; C->rchild = NULL; C->ltag = 0; C->rtag = 0;
  D->lchild = NULL; D->rchild = G; D->ltag = 0; D->rtag = 0;
  E->lchild = NULL; E->rchild = NULL; E->ltag = 0; E->rtag = 0;
  F->lchild = NULL; F->rchild = NULL; F->ltag = 0; F->rtag = 0;
  G->lchild = NULL; G->rchild = NULL; G->ltag = 0; G->rtag = 0;
  
  printf("In-order traversal of original tree:\n");
  InOrderTraverse(A);
  printf("\n");

  A = CreateInOrderThreadedTree(A);

  { ThreadNode *l = InOrderFindLast(A); ThreadNode *n = InOrderFindNext(A);
    printf("The Last node and Next node in in-order of A is: %c, %c\n", l ? l->data : 'N', n ? n->data : 'N'); }
  { ThreadNode *l = InOrderFindLast(B); ThreadNode *n = InOrderFindNext(B);
    printf("The Last node and Next node in in-order of B is: %c, %c\n", l ? l->data : 'N', n ? n->data : 'N'); }
  { ThreadNode *l = InOrderFindLast(C); ThreadNode *n = InOrderFindNext(C);
    printf("The Last node and Next node in in-order of C is: %c, %c\n", l ? l->data : 'N', n ? n->data : 'N'); }
  { ThreadNode *l = InOrderFindLast(D); ThreadNode *n = InOrderFindNext(D);
    printf("The Last node and Next node in in-order of D is: %c, %c\n", l ? l->data : 'N', n ? n->data : 'N'); }
  { ThreadNode *l = InOrderFindLast(E); ThreadNode *n = InOrderFindNext(E);
    printf("The Last node and Next node in in-order of E is: %c, %c\n", l ? l->data : 'N', n ? n->data : 'N'); }
  { ThreadNode *l = InOrderFindLast(F); ThreadNode *n = InOrderFindNext(F);
    printf("The Last node and Next node in in-order of F is: %c, %c\n", l ? l->data : 'N', n ? n->data : 'N'); }
  { ThreadNode *l = InOrderFindLast(G); ThreadNode *n = InOrderFindNext(G);
    printf("The Last node and Next node in in-order of G is: %c, %c\n", l ? l->data : 'N', n ? n->data : 'N'); }

  return 0;
}