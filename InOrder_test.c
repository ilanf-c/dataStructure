#include "global.h"
#include "InOrderThreadBinTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Helper: collect inorder traversal into buffer (matches InOrderTraverse behavior) */
static void collect_inorder(ThreadNode *T, char *buf, int *pos) {
    if (!T) return;
    collect_inorder(T->lchild, buf, pos);
    buf[(*pos)++] = T->data;
    buf[(*pos)++] = ' ';
    collect_inorder(T->rchild, buf, pos);
}

int testInOrder(){
    printf("\n**TEST[testInOrder]**\n");

      /* build the same 7-node tree as before */
      ThreadNode *A = malloc(sizeof(ThreadNode));
      ThreadNode *B = malloc(sizeof(ThreadNode));
      ThreadNode *C = malloc(sizeof(ThreadNode));
      ThreadNode *D = malloc(sizeof(ThreadNode));
      ThreadNode *E = malloc(sizeof(ThreadNode));
      ThreadNode *F = malloc(sizeof(ThreadNode));
      ThreadNode *G = malloc(sizeof(ThreadNode));
      if (!A||!B||!C||!D||!E||!F||!G) return 1;
      A->data = 'A'; B->data = 'B'; C->data = 'C'; D->data = 'D';
      E->data = 'E'; F->data = 'F'; G->data = 'G';
      A->lchild = B; A->rchild = C; A->ltag = 0; A->rtag = 0;
      B->lchild = D; B->rchild = E; B->ltag = 0; B->rtag = 0;
      C->lchild = F; C->rchild = NULL; C->ltag = 0; C->rtag = 0;
      D->lchild = NULL; D->rchild = G; D->ltag = 0; D->rtag = 0;
      E->lchild = NULL; E->rchild = NULL; E->ltag = 0; E->rtag = 0;
      F->lchild = NULL; F->rchild = NULL; F->ltag = 0; F->rtag = 0;
      G->lchild = NULL; G->rchild = NULL; G->ltag = 0; G->rtag = 0;

      /* collect inorder into buffer */
      char buf[64] = {0};
      int pos = 0;
      collect_inorder(A, buf, &pos);
      buf[pos] = '\0';
      const char *expected = "D G B E A F C ";
      printf("In-order traversal: '%s'\n", buf);

      if (strcmp(buf, expected) != 0) {
          fprintf(stderr, "InOrder traversal mismatch: expected '%s' got '%s'\n", expected, buf);
          /* free nodes */
          free(A); free(B); free(C); free(D); free(E); free(F); free(G);
          return 1;
      }

      /* test threading functions */
      A = CreateInOrderThreadedTree(A);
      /* inorder sequence array for lookup */
      char seq[] = {'D','G','B','E','A','F','C'};
      ThreadNode *nodes[7] = {D,G,B,E,A,F,C};
      /* expected predecessor and successor indices */
      int pred_idx[] = {-1,0,1,2,3,4,5};
      int succ_idx[] = {1,2,3,4,5,6,-1};

      for (int k = 0; k < 7; ++k) {
          ThreadNode *n = nodes[k];
          ThreadNode *p = InOrderFindLast(n);
          ThreadNode *s = InOrderFindNext(n);
          char exp_p = (pred_idx[k] == -1) ? 'N' : seq[pred_idx[k]];
          char exp_s = (succ_idx[k] == -1) ? 'N' : seq[succ_idx[k]];
          char got_p = p ? p->data : 'N';
          char got_s = s ? s->data : 'N';
          if (got_p != exp_p || got_s != exp_s) {
              fprintf(stderr, "Node %c: expected (p=%c,s=%c) got (p=%c,s=%c)\n",
                      n->data, exp_p, exp_s, got_p, got_s);
              free(A); free(B); free(C); free(D); free(E); free(F); free(G);
              return 1;
          }
      }

      printf("InOrder threading tests passed\n");
      free(A); free(B); free(C); free(D); free(E); free(F); free(G);
      return 0;
}