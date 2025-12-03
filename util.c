#include "util.h"

#include <stdio.h>

void Visit(ThreadNode *node) {
  if (node) {
    printf("%c ", node->data);
  }
}