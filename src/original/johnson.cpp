#include "johnson.h"
#include "bellman_ford.h"
#include "dijkstra.h"

#ifdef DEBUG
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#endif

bool johnson(graph_generator::OriginalGraph G, unsigned int source, size_t n, std::vector<std::vector<double>>& d) {
	
	// Krok 0: Inicjalizacja zmiennych
	d.clear();
	std::vector<double> h;

	// Krok 1: Utworzenie G2 poprzez dodanie nowego wierzcholka S
	// z wagami 0 do kazdego wierzcholka
	size_t G2_size = n + 1;
	// TODO enkapsulacja
	graph_generator::OriginalGraph G2 = new graph_generator::Weight*[G2_size];
	graph_generator::Weight* s = new graph_generator::Weight[G2_size] {};
	G2[0] = s;

	for (int i = 0; i < n; ++i) {
		G2[i + 1] = new graph_generator::Weight[G2_size];
		for (int j = 0; j < n; j++)
			G2[i + 1][j + 1] = G[i][j];
		// Do wierzcholka S nie wchodzi zadna krawedz
		G2[i + 1][0] = graph_generator::NO_EDGE; 
	}

	// Krok 2: sprawdzenie wystepowania ujemnych cykli
	if (!bellman_ford(G2, 0, G2_size, h))
		return false;

	// Krok 3: nadanie nieujemnych wartosci krawedzi w grafie G
	for (int u = 0; u < n; ++u) {
		for (int v = 0; v < n; ++v) {
			int edgeWeight = G[u][v];
			if (edgeWeight != graph_generator::NO_EDGE) {
				G[u][v] = G[u][v] + h[u + 1] - h[v + 1]; // +1 z uwagi na dodany wierzcholek S w G2
			}
		}
	}

	// Krok 4: obliczenie wartosci macierzy d
	for (int u = 0; u < n; ++u) {
		std::vector<double> k;
		d.push_back(k);
		dijkstra(G, u, n, d[u]);
		for (int v = 0; v < n; ++v) {
			d[u][v] = d[u][v] + h[v + 1] - h[u + 1];
		}
	}

	return true;
}

void original_johnson(std::shared_ptr<graph_generator> graph) {
	graph_generator::OriginalGraph G = graph->original_graph();
	std::vector<std::vector<double>> d;
	johnson(G, 0, graph->size(), d);
#ifdef _DEBUG
	if (d.empty())
		std::cout << "Wykryto ujemny cykl" << std::endl;
	else {
		for (int i = 0; i < d.size(); ++i)
			for (int j = 0; j < d.size(); ++j)
				std::cout << j << " --> " << i << " : " << d[j][i] << std::endl;
	}
#endif
}
