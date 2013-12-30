#include "breadth_first.h"

#include <iostream>
#include <queue>
#include "../common/graph_generator.h"

void breadth_first(int **G, int *V, size_t n) {
  std::queue<int> kolejka;
  for (size_t i = 0; i < n; i++) {
    V[i] = 0;
  }

  kolejka.push(0);

  while (!kolejka.empty()) {
    int s = kolejka.front();
    kolejka.pop();
    std::cout << s << " ";

    V[s] = 1;
    for (size_t k = 0; k < n; k++) {
      if (G[s][k] != 0) {
        if (V[k] == 0) {
          V[k] = 1;
          kolejka.push(k);
        }
      }
    }
  }
}

void original_breadth_first_sample(std::shared_ptr<graph_generator> graph) {
  int *V = new int[graph->size()];

  breadth_first(graph->original_graph(), V, graph->size());
  delete[] V;
}
