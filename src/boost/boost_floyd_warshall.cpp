#include "boost_floyd_warshall.h"

#ifdef DEBUG
#include <iomanip>
#include <iostream>
#endif
#include <boost/multi_array.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>

void boost_floyd_warshall(std::shared_ptr<graph_generator> graph) {
  typedef boost::multi_array<zbp::weight, 2> array_type;
  array_type D(boost::extents[graph->size()][graph->size()]);

  boost::floyd_warshall_all_pairs_shortest_paths(*graph->boost_weighted_graph(), D);

#ifdef DEBUG
  std::cout << "       ";
  for (size_t k = 0; k < graph->size(); ++k) {
    std::cout << std::setw(5) << k;
  }
  std::cout << std::endl;
  for (size_t i = 0; i < graph->size(); ++i) {
    std::cout << std::setw(3) << i << " -> ";
    for (size_t j = 0; j < graph->size(); ++j) {
      if (D[i][j] == (std::numeric_limits<int>::max)()) {
        std::cout << std::setw(5) << "x";
      } else {
        std::cout << std::setw(5) << D[i][j];
      }
    }
    std::cout << std::endl;
  }
#endif
}
