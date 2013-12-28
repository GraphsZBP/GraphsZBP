#include "sample_graph.h"

const int n = 7;

int** original_sample_graph() {
  int **g = new int*[n];
  //                  0  1  2  3  4  5  6
  g[0] = new int[n] { 1, 1, 0, 1, 1, 0, 0 };
  g[1] = new int[n] { 1, 1, 1, 0, 1, 0, 0 };
  g[2] = new int[n] { 0, 1, 1, 0, 0, 0, 1 };
  g[3] = new int[n] { 1, 0, 0, 1, 1, 0, 1 };
  g[4] = new int[n] { 1, 1, 0, 1, 1, 1, 0 };
  g[5] = new int[n] { 0, 0, 0, 0, 1, 1, 0 };
  g[6] = new int[n] { 0, 0, 1, 1, 0, 0, 1 };
  return g;
}

void free_original_sample_graph(int** g) {
  for (int i = 0; i < n; i++) {
    delete[] g[i];
  }
  delete[] g;
}
