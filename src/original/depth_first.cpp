#include <iostream>

void zwiedzaj(int **G, int *V, int i, int n);

void szukaj(int **G, int *V, int n) {
  int i;
  for (i = 0; i < n; i++) {
    V[i] = 0;
  }
  for (i = 0; i < n; i++) {
    if (V[i] == 0) {
      zwiedzaj(G, V, i, n);
    }
  }
}

void zwiedzaj(int **G, int *V, int i, int n) {
  std::cout << i << " ";
  V[i] = 1;
  for (int k = 0; k < n; k++) {
    if (G[i][k] != 0) {
      if (V[k] == 0) {
        zwiedzaj(G, V, k, n);
      }
    }
  }
}

