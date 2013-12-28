#include "breadth_first.h"

#include <iostream>
#include <queue>

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
  int *G[n], V[n];
  //                  0  1  2  3  4  5  6
  G[0] = new int[n] { 1, 1, 0, 1, 1, 0, 0 };
  G[1] = new int[n] { 1, 1, 1, 0, 1, 0, 0 };
  G[2] = new int[n] { 0, 1, 1, 0, 0, 0, 1 };
  G[3] = new int[n] { 1, 0, 0, 1, 1, 0, 1 };
  G[4] = new int[n] { 1, 1, 0, 1, 1, 1, 0 };
  G[5] = new int[n] { 0, 0, 0, 0, 1, 1, 0 };
  G[6] = new int[n] { 0, 0, 1, 1, 0, 0, 1 };

  breadth_first(G, V, n);
}
