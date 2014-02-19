#include "breadth_first.h"

#include <iostream>
#include <queue>

void breadth_first(zbp::distance_matrix G, bool *V, size_t n) {
  std::queue<int> kolejka;
  for (size_t i = 0; i < n; i++) {
    V[i] = false;
  }

  kolejka.push(0);

  while (!kolejka.empty()) {
    int s = kolejka.front();
    kolejka.pop();
#ifdef _DEBUG
    std::cout << s << " ";
#endif

    V[s] = 1;
    for (size_t k = 0; k < n; k++) {
      if (G[s][k] != zbp::NO_EDGE) {
        if (V[k] == false) {
          V[k] = true;
          kolejka.push(k);
        }
      }
    }
  }
}

void original_breadth_first(std::shared_ptr<graph_generator> graph) {
  bool *V = new bool[graph->size()];

  breadth_first(graph->original_graph(), V, graph->size());

#ifdef _DEBUG
  std::cout << std::endl;
#endif

  delete[] V;
}
