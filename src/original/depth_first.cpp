#include "depth_first.h"
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


void original_depth_first_sample() {
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
  szukaj(G, V, n);
}
