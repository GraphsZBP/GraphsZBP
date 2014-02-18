#include "floyd_warshall.h"

#include <algorithm>
#ifdef DEBUG
#include <iostream>
#endif
#include <queue>

void floyd_warshall(zbp::distance_matrix G, size_t n) {
  for (size_t k = 0; k < n; k++) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        G[i][j] = std::min(G[i][j], G[i][k] + G[k][j]);
      }
    }
  }
}

void original_floyd_warshall(std::shared_ptr<graph_generator> graph) {
  zbp::distance_matrix m_original_graph = graph->original_graph();

  zbp::distance_matrix G = new zbp::weight*[graph->size()];
  for (size_t i = 0; i < graph->size(); i++) {
    G[i] = new zbp::weight[graph->size()];
    std::copy(m_original_graph[i], m_original_graph[i] + graph->size(), G[i]);
  }

  floyd_warshall(G, graph->size());
#ifdef DEBUG
  for (size_t i = 0; i < graph->size(); i++) {
    for (size_t j = 0; j < graph->size(); j++) {
      if (G[i][j] == zbp::NO_EDGE) {
        std::cout << i << " --> " << j << ": brak" << std::endl;
      } else {
        std::cout << i << " --> " << j << ": " << G[i][j] << std::endl;
      }
    }
  }
#endif

  for (size_t i = 0; i < graph->size(); i++) {
    delete[] G[i];
  }
  delete[] G;
}
