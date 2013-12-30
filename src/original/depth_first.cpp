#include "depth_first.h"

#include <iostream>
#include "../common/graph_generator.h"

void depth_first_visit(int **G, int *V, int i, int n);

void depth_first(int **G, int *V, int n) {
  int i;
  for (i = 0; i < n; i++) {
    V[i] = 0;
  }
  for (i = 0; i < n; i++) {
    if (V[i] == 0) {
      depth_first_visit(G, V, i, n);
    }
  }
}

void depth_first_visit(int **G, int *V, int i, int n) {
  std::cout << i << " ";
  V[i] = 1;
  for (int k = 0; k < n; k++) {
    if (G[i][k] != 0) {
      if (V[k] == 0) {
        depth_first_visit(G, V, k, n);
      }
    }
  }
}

void original_depth_first_sample() {
  const int n = 7;
  int *V = new int[n];
  graph_generator graph;

  depth_first(graph.original_graph(), V, n);
  delete[] V;
}
