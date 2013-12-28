#include "breadth_first.h"

#include <iostream>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/breadth_first_search.hpp>

class bfs_print_visitor: public boost::default_bfs_visitor {
public:
  template<typename Vertex, typename Graph>
  void discover_vertex(Vertex u, const Graph & g) const {
    std::cout << u << " ";
  }
};

void boost_breadth_first_sample() {
  const int n = 7;

  typedef boost::adjacency_matrix<boost::undirectedS> Graph;
  Graph g(n);
  boost::add_edge(0, 1, g);
  boost::add_edge(0, 3, g);
  boost::add_edge(0, 4, g);
  boost::add_edge(1, 2, g);
  boost::add_edge(1, 4, g);
  boost::add_edge(2, 6, g);
  boost::add_edge(3, 4, g);
  boost::add_edge(3, 6, g);
  boost::add_edge(4, 5, g);

  bfs_print_visitor vis;

  boost::breadth_first_search(g, boost::vertex(0, g), boost::visitor(vis));
}

