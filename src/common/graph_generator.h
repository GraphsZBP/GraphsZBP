#pragma once

#include <limits.h>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "graph_types.h"

class graph_generator {
private:
	typedef boost::property<boost::edge_weight_t, zbp::weight> WeightProperty;

public:
	typedef boost::adjacency_matrix<boost::undirectedS> BoostSimpleGraph;

	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
		boost::no_property, WeightProperty> BoostWeightedGraph;

	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
		boost::property< boost::edge_weight_t, int, boost::property< boost::edge_weight2_t, int > > > BoostJohnsonGraph;

	typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property,
		WeightProperty> BoostWeightedDirectedGraph;
	typedef std::pair < int, int >Edge;

private:
	static zbp::weight MAX_WEIGHT;

	const size_t m_size;
	zbp::distance_matrix m_original_graph;
	std::shared_ptr<BoostSimpleGraph> m_boost_graph;
	BoostWeightedGraph m_boost_weighted_graph;
	BoostWeightedDirectedGraph m_boost_weighted_directed_graph;
	BoostJohnsonGraph m_boost_johnson_graph;

	size_t generate_edge_number(size_t i);
	void enhance_graph_connectivity();
	void original_to_boost();

public:
	graph_generator();
	graph_generator(size_t size, int fill);
	~graph_generator();

	void print();
	const size_t size();
	zbp::distance_matrix original_graph();
	std::shared_ptr<BoostSimpleGraph> boost_graph();
	BoostSimpleGraph::vertex_descriptor boost_initial_vertex();
	BoostWeightedGraph boost_weighted_graph();
	BoostWeightedDirectedGraph boost_weighted_directed_graph();
	BoostJohnsonGraph boost_johnson_graph();
};
