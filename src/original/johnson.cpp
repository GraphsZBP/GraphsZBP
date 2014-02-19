#include "johnson.h"
#include "bellman_ford.h"
#include "dijkstra.h"

#ifdef _DEBUG
#include <iostream>
#include <iomanip>
#endif

bool johnson(zbp::distance_matrix G, unsigned int source, size_t n, std::vector<std::vector<double>>& d) {

  // Krok 1: Inicjalizacja zmiennych
  d.clear();
  std::vector<double> h;

  // Krok 2: Utworzenie G2 poprzez dodanie nowego wierzcholka S
  // z wagami 0 do kazdego wierzcholka
  size_t G2_size = n + 1;
  zbp::distance_matrix G2 = new zbp::weight*[G2_size];
  zbp::weight* s = new zbp::weight[G2_size] { };
  G2[0] = s;

  for (unsigned int i = 0; i < n; ++i) {
    G2[i + 1] = new zbp::weight[G2_size];
    for (unsigned int j = 0; j < n; j++)
      G2[i + 1][j + 1] = G[i][j];
    // Do wierzcholka S nie wchodzi zadna krawedz
    G2[i + 1][0] = zbp::NO_EDGE;
  }

  // Krok 3: sprawdzenie wystepowania ujemnych cykli
  if (!bellman_ford(G2, 0, G2_size, h))
    return false;

  // Krok 4: nadanie nieujemnych wartosci krawedzi w grafie G
  for (unsigned int u = 0; u < n; ++u) {
    for (unsigned int v = 0; v < n; ++v) {
      int edgeWeight = G[u][v];
      if (edgeWeight != zbp::NO_EDGE) {
        G[u][v] = G[u][v] + h[u + 1] - h[v + 1]; // +1 z uwagi na dodany wierzcholek S w G2
      }
    }
  }

  // Krok 5: obliczenie wartosci macierzy d
  for (unsigned int u = 0; u < n; ++u) {
    std::vector<double> k;
    d.push_back(k);
    dijkstra(G, u, n, d[u]);
    for (unsigned int v = 0; v < n; ++v) {
      d[u][v] = d[u][v] + h[v + 1] - h[u + 1];
    }
  }

  return true;
}

void original_johnson(std::shared_ptr<graph_generator> graph) {
  zbp::distance_matrix G = graph->original_graph();
  std::vector<std::vector<double>> D;
  johnson(G, 0, graph->size(), D);

#ifdef _DEBUG
  int V = graph->size();
  std::cout << "       ";
  for (int k = 0; k < V; ++k)
    std::cout << std::setw(5) << k;
  std::cout << std::endl;
  for (int i = 0; i < V; ++i) {
    std::cout << std::setw(3) << i << " -> ";
    for (int j = 0; j < V; ++j) {
      if (D[i][j] == (std::numeric_limits<int>::max)())
        std::cout << std::setw(5) << "x";
      else
        std::cout << std::setw(5) << D[i][j];
    }
    std::cout << std::endl;
  }
#endif
}
