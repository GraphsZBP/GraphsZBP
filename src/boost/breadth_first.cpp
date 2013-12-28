#include "breadth_first.h"

#include <iostream>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include "sample_graph.h"

class bfs_print_visitor: public boost::default_bfs_visitor {
public:
  template<typename Vertex, typename Graph>
  void discover_vertex(Vertex u, const Graph & g) const {
    std::cout << u << " ";
  }
};

void boost_breadth_first_sample() {
  boost::adjacency_matrix<boost::undirectedS> g = boost_sample_graph();
  bfs_print_visitor vis;

  boost::breadth_first_search(g, boost::vertex(0, g), boost::visitor(vis));
}
