#include "breadth_first.h"

#include <iostream>
#include <queue>
#include "sample_graph.h"

void breadth_first(int **G, int *V, int n) {
  std::queue<int> kolejka;
  for (int i = 0; i < n; i++) {
    V[i] = 0;
  }

  kolejka.push(0);

  while (!kolejka.empty()) {
    int s = kolejka.front();
    kolejka.pop();
    std::cout << s << " ";

    V[s] = 1;
    for (int k = 0; k < n; k++) {
      if (G[s][k] != 0) {
        if (V[k] == 0) {
          V[k] = 1;
          kolejka.push(k);
        }
      }
    }
  }
}

void original_breadth_first_sample() {
  const int n = 7;
  int V[n];
  int** G = original_sample_graph();

  breadth_first(G, V, n);

  free_original_sample_graph(G);
}
