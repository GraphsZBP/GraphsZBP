#ifndef GRAPH_GENERATOR_H_
#define GRAPH_GENERATOR_H_

#include <map>
#include <string>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/adjacency_list.hpp>

class graph_generator {
public:
  typedef unsigned int AdjacencyMatrixElement;
  typedef boost::adjacency_matrix<boost::undirectedS> BoostSimpleGraph;
  typedef AdjacencyMatrixElement** OriginalGraph;

  typedef boost::property<boost::edge_weight_t, AdjacencyMatrixElement> Weight;
  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
      boost::no_property, Weight> BoostWeightedGraph;

private:
  const size_t m_size;
  OriginalGraph m_original_graph;
  std::shared_ptr<BoostSimpleGraph> m_boost_graph;
  BoostWeightedGraph m_boost_weighted_graph;

  size_t generate_edge_number(size_t i);
  void enhance_graph_connectivity();
  void original_to_boost();

public:
  static AdjacencyMatrixElement NO_EDGE;

  graph_generator();
  graph_generator(size_t size, int fill);
  ~graph_generator();

  void print();
  const size_t size();
  OriginalGraph original_graph();
  std::shared_ptr<BoostSimpleGraph> boost_graph();
  BoostSimpleGraph::vertex_descriptor boost_initial_vertex();
  BoostWeightedGraph boost_weighted_graph();
};

#endif /* GRAPH_GENERATOR_H_ */
