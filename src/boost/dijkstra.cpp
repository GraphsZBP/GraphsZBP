#include "dijkstra.h"

#ifdef DEBUG
#include <iostream>
#endif
#include <boost/multi_array.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>

using namespace boost;

void boost_dijkstra(std::shared_ptr<graph_generator> graph) {
	graph_generator::BoostWeightedGraph g =
			graph->boost_weighted_graph();
	typedef graph_traits<graph_generator::BoostWeightedGraph>::vertex_descriptor vertex_descriptor;
	std::vector<vertex_descriptor> p(num_vertices(g));
	std::vector<int> d(num_vertices(g));
	dijkstra_shortest_paths(g, graph->boost_initial_vertex(), predecessor_map(&p[0]).distance_map(&d[0]));

#ifdef DEBUG
	std::cout << "distances and parents:" << std::endl;
	graph_traits<graph_generator::BoostWeightedGraph>::vertex_iterator
			vi, vend;
	for (tie(vi, vend) = vertices(g); vi != vend; ++vi) {
		std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
		std::cout << "parent(" << *vi << ") = " << p[*vi] << std::endl;
	}
	std::cout << std::endl;
#endif
}
