

# DataStructure Learning

Small C playground that implements several classic data-structure exercises:
an in-order threaded binary tree, Kruskal/Prim minimum spanning tree solvers,
and Dijkstra/Floyd shortest-path routines. Everything is wired together with a
shared utility layer (priority queue, disjoint-set union, common types) and a
very small test harness.

## What’s Included
- **InOrderThreadBinTree** – create, thread, and traverse threaded binary trees.
- **MST** – Kruskal & Prim implementations that operate on adjacency matrices.
- **Short_path** – Dijkstra (priority queue driven) and Floyd–Warshall solvers.
- **util/global** – priority queue, DSU helpers, and common typedefs.
- **test runner** – `test.c` dispatches module-level tests from `*_test.c`.

## Requirements
- clang or gcc that understands C11
- `make`

## Building
- `make` – compiles everything except the test harness into `build/main`
- `make test-bin` – builds the standalone test binary `build/test`
- `make clean` – removes `build/`

## Running Tests
- `make test` – builds (if needed) and executes every registered test
- `make test TEST=InOrder` – run just one test (`InOrder`, `MST`, `ShortPath`, …)

## Adding a New Test
1. Create `your_feature_test.c` and expose `int testYourFeature(void);`.
2. Update `test.c`:
   - bump `MAX_TEST`
   - forward-declare the new `testYourFeature`
   - extend the `TEST_NAME` enum plus the `test_names` table
   - add a `case` inside `run_test`, and invoke it in the `"all"` branch
3. Edit the `TEST_OBJS` list in the `Makefile` to include the new object.

## Repository Layout
- `InOrderThreadBinTree.*` – threaded binary tree logic
- `MST.*` – graph MST algorithms
- `Short_path.*` – single/all-pairs shortest paths
- `util.*`, `global.h` – shared helpers
- `*_test.c`, `test.c` – tests + runner
- `Makefile` – builds both app and tests