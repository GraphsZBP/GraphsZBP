#include "dijkstra.h"

// TODO check INFINITY predefined variable
#define INFINITE INT_MAX
#ifdef DEBUG
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#endif

/**
 * http://sun.aei.polsl.pl/~sdeor/students/aa/graf_dijkstra.pdf
 */
std::vector<double> dijkstra(graph_generator::OriginalGraph G,  unsigned int source, size_t n) {
	int u;
	int min_d_in_q = INFINITE;

	std::vector<double> d;
	std::vector<double> p;
	std::set<int> S;
	std::set<int> Q;

	// Inicjalizacja zmiennych
	for (unsigned int i = 0; i < n; ++i) {
		d.push_back(INFINITE);
		p.push_back(0);
		Q.insert(i);
	}
	d[source] = 0;



	while(!Q.empty()) {
		// u := wierzcho�ek z Q o minimalnej warto�ci d;
		for (const int &q : Q) {
			int actual_d_value = d[q];
			if (min_d_in_q == INFINITE) {
				min_d_in_q = actual_d_value;
				u = q;
			}
			else if (actual_d_value < min_d_in_q){
				min_d_in_q = actual_d_value;
				u = q;
			}
		}

		// S := S + {u};
		if (min_d_in_q != INFINITE) {
			Q.erase(u);
			S.insert(u);
		}

		// for lista wierzcho�k�w v s�siaduj�cych z u -> relaksacja
		for (unsigned int v = 0; v < n; ++v) {
			int edgeWeight = G[u][v];
			if (edgeWeight != 0 && edgeWeight != graph_generator::NO_EDGE) {
				if (d[u] + edgeWeight < d[v]) {
					d[v] = d[u] + edgeWeight;
					p[v] = u;
				}
			}
		}
	}
	return d;
}

void original_dijkstra(std::shared_ptr<graph_generator> graph) {
	graph_generator::OriginalGraph G = graph->original_graph();

	std::vector<double> d = dijkstra(G, graph->size(), 0);
#ifdef DEBUG
	for(int i = 0; i < d.size(); ++i) {
		std::cout << 0 << " --> " << i << " : " << d[i];
	}
#endif
}
