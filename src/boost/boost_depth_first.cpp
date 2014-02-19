#include "boost_depth_first.h"

#ifdef _DEBUG
#include <iostream>
#endif
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/depth_first_search.hpp>
#include "../common/graph_generator.h"

class dfs_print_visitor: public boost::default_dfs_visitor {
public:
  template<typename Vertex, typename Graph>
  void discover_vertex(Vertex u, const Graph & g) const {
#ifdef _DEBUG
    std::cout << u << " ";
#endif
  }
};

void boost_depth_first(std::shared_ptr<graph_generator> graph) {
  dfs_print_visitor vis;

  boost::depth_first_search(*graph->boost_graph(), boost::visitor(vis));

#ifdef _DEBUG
  std::cout << std::endl;
#endif
}

