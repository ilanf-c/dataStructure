
#include <string.h>
#include <stdio.h>

/* Forward declarations for tests defined elsewhere */
int testInOrder();

/* Run a named test; return 0 on success or non-zero on unknown test */
int run_test(const char *name) {
  if (name == NULL || strcmp(name, "all") == 0) {
    printf("Running all tests:\n");
    testInOrder();
    return 0;
  }
  if (strcmp(name, "InOrder") == 0) {
    return testInOrder();
  }
  fprintf(stderr, "Unknown test '%s'\n", name);
  return 1;
}

int main(int argc, char **argv) {
  const char *which = (argc > 1) ? argv[1] : "all";
  return run_test(which);
}