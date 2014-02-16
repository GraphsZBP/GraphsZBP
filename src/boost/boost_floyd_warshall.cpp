#include "boost_floyd_warshall.h"

#ifdef DEBUG
#include <iostream>
#endif
#include <boost/multi_array.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>

void boost_floyd_warshall(std::shared_ptr<graph_generator> graph) {
  typedef boost::multi_array<zbp::weight, 2> array_type;
  array_type D(boost::extents[graph->size()][graph->size()]);

  boost::floyd_warshall_all_pairs_shortest_paths(*graph->boost_weighted_graph(), D);

#ifdef DEBUG
  for (size_t i = 0; i < graph->size(); i++) {
    for (size_t j = 0; j < graph->size(); j++) {
      if (D[i][j] == zbp::NO_EDGE) {
        std::cout << i << " --> " << j << ": brak" << std::endl;
      } else {
        std::cout << i << " --> " << j << ": " << D[i][j] << std::endl;
      }
    }
  }
#endif
}
