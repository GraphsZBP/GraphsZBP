#include "sample_graph.h"

boost::adjacency_matrix<boost::undirectedS> boost_sample_graph() {
  const int n = 7;
  boost::adjacency_matrix<boost::undirectedS> g(n);
  boost::add_edge(0, 1, g);
  boost::add_edge(0, 3, g);
  boost::add_edge(0, 4, g);
  boost::add_edge(1, 2, g);
  boost::add_edge(1, 4, g);
  boost::add_edge(2, 6, g);
  boost::add_edge(3, 4, g);
  boost::add_edge(3, 6, g);
  boost::add_edge(4, 5, g);

  return g;
}
