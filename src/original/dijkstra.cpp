#include "dijkstra.h"

#ifdef _DEBUG
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#endif

/**
 * http://sun.aei.polsl.pl/~sdeor/students/aa/graf_dijkstra.pdf
 */
bool dijkstra(zbp::distance_matrix G, unsigned int source, size_t n, std::vector<double>& d) {
	int u;
	int min_d_in_q = INT_MAX;
	
	std::vector<double> p;
	std::set<int> S;
	std::set<int> Q;

	// Inicjalizacja zmiennych
	for (unsigned int i = 0; i < n; ++i) {
		d.push_back(INT_MAX);
		p.push_back(0);
		Q.insert(i);
	}
	d[source] = 0;

	while(!Q.empty()) {
		// u := wierzcho³ek z Q o minimalnej wartoœci d;
		min_d_in_q = INT_MAX;
		for (const int &q : Q) {
			int actual_d_value = d[q];
			if (min_d_in_q == INT_MAX) {
				min_d_in_q = actual_d_value;
				u = q;
			}
			else if (actual_d_value < min_d_in_q){
				min_d_in_q = actual_d_value;
				u = q;
			}
		}

		// S := S + {u};
		if (min_d_in_q != INT_MAX) {
			Q.erase(u);
			S.insert(u);
		}

		// for lista wierzcho³ków v s¹siaduj¹cych z u -> relaksacja
		for (unsigned int v = 0; v < n; ++v) {
			int edgeWeight = G[u][v];
			if (edgeWeight != zbp::NO_EDGE) {
				if (d[u] + edgeWeight < d[v]) {
					d[v] = d[u] + edgeWeight;
					p[v] = u;
				}
			}
		}
	}
	return true;
}

void original_dijkstra(std::shared_ptr<graph_generator> graph) {
	zbp::distance_matrix G = graph->original_graph();
	std::vector<double> d;
	dijkstra(G, 0, graph->size(), d);
#ifdef _DEBUG
	for(int i = 0; i < d.size(); ++i) {
		std::cout << 0 << " --> " << i << " : " << d[i] << std::endl;
	}
#endif
}
