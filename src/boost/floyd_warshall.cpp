#include "floyd_warshall.h"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>

void boost_floyd_warshall(std::shared_ptr<graph_generator> graph) {
  graph_generator::AdjacencyMatrixElement D[7][7]; //FIXME

  boost::floyd_warshall_all_pairs_shortest_paths(graph->boost_weighted_graph(), D);

  for (size_t i = 0; i < graph->size(); i++) {
    for (size_t j = 0; j < graph->size(); j++) {
      if (D[i][j] == graph_generator::NO_EDGE) {
        std::cout << i << " --> " << j << ": brak" << std::endl;
      } else {
        std::cout << i << " --> " << j << ": " << D[i][j] << std::endl;
      }
    }
  }
}
