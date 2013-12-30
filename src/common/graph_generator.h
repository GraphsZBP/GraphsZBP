#ifndef GRAPH_GENERATOR_H_
#define GRAPH_GENERATOR_H_

#include <boost/graph/adjacency_matrix.hpp>

class graph_generator {
  int m_size;
  int** m_original_graph;
  boost::adjacency_matrix<boost::undirectedS> m_boost_graph;

  int generate_edge_number(int i);
  void enhance_graph_connectivity();

public:
  graph_generator();
  graph_generator(int size, int fill);
  ~graph_generator();

  void print();
  size_t size();
  int** original_graph();
  boost::adjacency_matrix<boost::undirectedS> boost_graph();
  boost::adjacency_matrix<boost::undirectedS>::vertex_descriptor boost_initial_vertex();
};

#endif /* GRAPH_GENERATOR_H_ */
