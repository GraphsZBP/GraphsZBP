#include "floyd_warshall.h"

#include <algorithm>
#ifdef _DEBUG
#include <iostream>
#include <iomanip>
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

  zbp::distance_matrix D = new zbp::weight*[graph->size()];
  for (size_t i = 0; i < graph->size(); i++) {
    D[i] = new zbp::weight[graph->size()];
    std::copy(m_original_graph[i], m_original_graph[i] + graph->size(), D[i]);
  }

  floyd_warshall(D, graph->size());

#ifdef _DEBUG
  std::cout << "       ";
  for (size_t k = 0; k < graph->size(); ++k) {
    std::cout << std::setw(5) << k;
  }
  std::cout << std::endl;
  for (size_t i = 0; i < graph->size(); ++i) {
    std::cout << std::setw(3) << i << " -> ";
    for (size_t j = 0; j < graph->size(); ++j) {
      if (D[i][j] == zbp::NO_EDGE) {
        std::cout << std::setw(5) << "x";
      } else {
        std::cout << std::setw(5) << D[i][j];
      }
    }
    std::cout << std::endl;
  }
#endif

  for (size_t i = 0; i < graph->size(); i++) {
    delete[] D[i];
  }
  delete[] D;
}
