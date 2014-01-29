/*
 * bellmanford.cpp
 *
 *  Created on: 29 sty 2014
 *      Author: Micha³
 */

#include "bellman_ford.h"

#ifdef DEBUG
#include <iostream>
#endif
#include <boost/multi_array.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;

void boost_bellman_ford(std::shared_ptr<graph_generator> graph) {
	graph_generator::BoostWeightedGraph g = graph->boost_weighted_graph();
	typedef graph_traits<graph_generator::BoostWeightedGraph>::vertex_descriptor vertex_descriptor;
	std::vector<vertex_descriptor> p(num_vertices(g));
	std::vector<int> d(num_vertices(g));
	bellman_ford_shortest_paths(g, num_vertices(g),distance_map(&d[0]).predecessor_map(&p[0]));

#ifdef DEBUG
	std::cout << "distances and parents:" << std::endl;
	graph_traits<graph_generator::BoostWeightedGraph>::vertex_iterator vi, vend;
	for (tie(vi, vend) = vertices(g); vi != vend; ++vi) {
		std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
		std::cout << "parent(" << *vi << ") = " << p[*vi] << std::endl;
	}
	std::cout << std::endl;
#endif
}
