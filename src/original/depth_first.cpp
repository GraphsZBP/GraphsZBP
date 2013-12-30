#include "depth_first.h"

#include <iostream>

void depth_first_visit(int **G, int *V, int i, size_t n);

void depth_first(int **G, int *V, size_t n) {
  size_t i;
  for (i = 0; i < n; i++) {
    V[i] = 0;
  }
  for (i = 0; i < n; i++) {
    if (V[i] == 0) {
      depth_first_visit(G, V, i, n);
    }
  }
}

void depth_first_visit(int **G, int *V, int i, size_t n) {
  std::cout << i << " ";
  V[i] = 1;
  for (size_t k = 0; k < n; k++) {
    if (G[i][k] != 0) {
      if (V[k] == 0) {
        depth_first_visit(G, V, k, n);
      }
    }
  }
}

void original_depth_first_sample(std::shared_ptr<graph_generator> graph) {
  int *V = new int[graph->size()];

  depth_first(graph->original_graph(), V, graph->size());
  delete[] V;
}
