#include "johnson.h"
#include "bellman_ford.h"
#include "dijkstra.h"



#ifdef DEBUG
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#endif

// TODO
bool johnson(graph_generator::OriginalGraph G, unsigned int source, size_t n, std::vector<double> d) {
	
	// Krok 1: sprawdzenie wystepowania ujemnych cykli
	if (!bellman_ford(G, source, n, d))
		return false;



	return true;
}

void original_johnson(std::shared_ptr<graph_generator> graph) {
	graph_generator::OriginalGraph G = graph->original_graph();
	std::vector<double> d;
	johnson(G, 0, graph->size(), d);
#ifdef _DEBUG
	if (d.empty())
		std::cout << "Wykryto ujemny cykl" << std::endl;
	else {
		for (int i = 0; i < d.size(); ++i)
			std::cout << 0 << " --> " << i << " : " << d[i] << std::endl;
	}
#endif
}
