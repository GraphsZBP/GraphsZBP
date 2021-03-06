#include "boost_breadth_first.h"

#ifdef _DEBUG
#include <iostream>
#endif
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include "../common/graph_generator.h"

class bfs_print_visitor: public boost::default_bfs_visitor {
public:
  template<typename Vertex, typename Graph>
  void discover_vertex(Vertex u, const Graph & g) const {
#ifdef _DEBUG
    std::cout << u << " ";
#endif
  }
};

void boost_breadth_first(std::shared_ptr<graph_generator> graph) {
  bfs_print_visitor vis;

  boost::breadth_first_search(*(graph->boost_graph()), graph->boost_initial_vertex(), boost::visitor(vis));

#ifdef _DEBUG
  std::cout << std::endl;
#endif
}
