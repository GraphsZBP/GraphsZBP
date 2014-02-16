#include "boost_johnson.h"

#ifdef DEBUG
#include <iostream>
#endif
#include <boost/multi_array.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#include <boost/graph/graph_traits.hpp>

#include <boost/config.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

using namespace boost;

void boost_johnson(std::shared_ptr<graph_generator> graph) {
	graph_generator::BoostJohnsonGraph g = *graph->boost_johnson_graph();
	int V = num_vertices(g);
	std::vector<int> d(V, (std::numeric_limits < int >::max)());
	int** D = new int*[V];
	for (int d = 0; d < V; d++)
	{
		D[d] = new int[V];
	}
	johnson_all_pairs_shortest_paths(g, D, distance_map(&d[0]));

#ifdef DEBUG
  std::cout << "       ";
	for (int k = 0; k < V; ++k)
		std::cout << std::setw(5) << k;
	std::cout << std::endl;
	for (int i = 0; i < V; ++i) {
		std::cout << std::setw(3) << i << " -> ";
		for (int j = 0; j < V; ++j) {
			if (D[i][j] == (std::numeric_limits<int>::max)())
				std::cout << std::setw(5) << "inf";
			else
				std::cout << std::setw(5) << D[i][j];
		}
		std::cout << std::endl;
	}
#endif
}
