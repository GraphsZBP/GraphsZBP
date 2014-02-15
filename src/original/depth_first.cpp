#include "depth_first.h"

#ifdef DEBUG
#include <iostream>
#endif

void depth_first_visit(zbp::distance_matrix G, bool *V, int i,
    size_t n);

void depth_first(zbp::distance_matrix G, bool *V, size_t n) {
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

void depth_first_visit(zbp::distance_matrix G, bool *V, int i,
    size_t n) {
#ifdef DEBUG
  std::cout << i << " ";
#endif
  V[i] = 1;
  for (size_t k = 0; k < n; k++) {
    if (G[i][k] != graph_generator::NO_EDGE) {
      if (V[k] == 0) {
        depth_first_visit(G, V, k, n);
      }
    }
  }
}

void original_depth_first_sample(std::shared_ptr<graph_generator> graph) {
  bool *V = new bool[graph->size()];

  depth_first(graph->original_graph(), V, graph->size());
  delete[] V;
}
