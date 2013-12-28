#include "depth_first.h"

#include <iostream>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "sample_graph.h"

class dfs_print_visitor: public boost::default_dfs_visitor {
public:
  template<typename Vertex, typename Graph>
  void discover_vertex(Vertex u, const Graph & g) const {
    std::cout << u << " ";
  }
};

void boost_depth_first_sample() {
  boost::adjacency_matrix<boost::undirectedS> g = boost_sample_graph();
  dfs_print_visitor vis;

  boost::depth_first_search(g, boost::visitor(vis));
}

