#include "bellman_ford.h"

#ifdef DEBUG
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#endif

/**
 * @return false w przypadku wykrycia ujemnego cyklu
 */
bool bellman_ford(zbp::distance_matrix G, unsigned int source, size_t n, std::vector<double>& d) {
	d.clear();
	std::vector<double> p;

	// Krok 1:Inicjalizacja zmiennych
	for (int i = 0; i < n; ++i) {
		d.push_back(INT_MAX);
		p.push_back(0);
	}
	d[source] = 0;

	// Krok 2: powtórna relaksacja
	for (int i = 1; i < n; ++i) {
		for (int u = 0; u < n; ++u) {
			for (int v = 0; v < n; ++v) {
				int edgeWeight = G[u][v];
				if (edgeWeight != graph_generator::NO_EDGE) {
					if (d[u] + edgeWeight < d[v]) {
						d[v] = d[u] + edgeWeight;
						p[v] = u;
					}
				}
			}
		}
	}

	// Krok 3: sprawdzanie wyst¹pieñ ujemnych cykli
	for (int u = 0; u < n; ++u) {
		for (int v = 0; v < n; ++v) {
			int edgeWeight = G[u][v];
			if (edgeWeight != graph_generator::NO_EDGE) {
				if (d[u] + edgeWeight < d[v]) {
					d.clear();
					false;
				}
			}
		}
	}
	return true;
}

void original_bellman_ford(std::shared_ptr<graph_generator> graph) {
	zbp::distance_matrix G = graph->original_graph();
	std::vector<double> d;
	bellman_ford(G, 0, graph->size(), d);
#ifdef _DEBUG
	if (d.empty())
		std::cout << "Wykryto ujemny cykl" << std::endl;
	else {
		for (int i = 0; i < d.size(); ++i)
			std::cout << 0 << " --> " << i << " : " << d[i] << std::endl;
	}
#endif
}
