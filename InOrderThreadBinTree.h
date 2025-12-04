#ifndef _IN_ORDER_H
#define _IN_ORDER_H
#include "util.h"
#include "global.h"

void InOrderVisit(ThreadNode *node, ThreadNode **pre);

void InOrderThreading(ThreadNode *T, ThreadNode **pre);

ThreadTree CreateInOrderThreadedTree(ThreadTree T);

ThreadNode *InOrderFindLast(ThreadNode *node);

ThreadNode *InOrderFindNext(ThreadNode *node);

void InOrderTraverse(ThreadNode *T);
#endif