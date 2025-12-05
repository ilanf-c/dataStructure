
#include <string.h>
#include <stdio.h>

#define MAX_TEST 5
/* Forward declarations for tests defined elsewhere */
int testInOrder();
int testMST();
int testShortPath();
int testTopo();
int testInsertSort();

typedef enum{
  IN_ORDER_THREAD,
  MST,
  SHORT_PATH,
  TOPOLOGICAL_SORT,
  INSERT_SORT,
} TEST_NAME;

static struct {
  char *str;
  TEST_NAME name;
} test_names[MAX_TEST] = {
  {"InOrder", IN_ORDER_THREAD},
  {"MST", MST},
  {"ShortPath", SHORT_PATH},
  {"TOPO", TOPOLOGICAL_SORT},
  {"InsertSort", INSERT_SORT},
};

TEST_NAME lookup(const char *name){
  for(int i = 0; i<MAX_TEST; ++i)
    if (strcmp(name, test_names[i].str) == 0)
      return test_names[i].name;
  return -1;
}

/* Run a named test; return 0 on success or non-zero on unknown test */
int run_test(const char *name) {
  if (name == NULL || strcmp(name, "all") == 0) {
    printf("Running all tests:\n");
    testInOrder();
    testMST();
    testShortPath();
    testTopo();
    testInsertSort();
    return 0;
  }
  switch (lookup(name)) {
    case IN_ORDER_THREAD: return testInOrder();
    case MST: return testMST();
    case SHORT_PATH: return testShortPath();
    case TOPOLOGICAL_SORT: return testTopo();
    case INSERT_SORT: return testInsertSort();
    default: break;
  }
  fprintf(stderr, "Unknown test '%s'\n", name);
  return 1;
}

int main(int argc, char **argv) {
  const char *which = (argc > 1) ? argv[1] : "all";
  return run_test(which);
}