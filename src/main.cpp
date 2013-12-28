#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/range/irange.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include "original/depth_first.h"

class dfs_print_visitor: public boost::default_dfs_visitor {
public:
  template<typename Vertex, typename Graph>
  void discover_vertex(Vertex u, const Graph & g) const {
    std::cout << u << " ";
  }
  template<typename Vertex, typename Graph>
  void finish_vertex(Vertex u, const Graph & g) const {
  }
};


int main() {
  const int n = 7;
  int *G[n], V[n];
  //                  0  1  2  3  4  5  6
  G[0] = new int[n] { 1, 1, 0, 1, 1, 0, 0 };
  G[1] = new int[n] { 1, 1, 1, 0, 1, 0, 0 };
  G[2] = new int[n] { 0, 1, 1, 0, 0, 0, 1 };
  G[3] = new int[n] { 1, 0, 0, 1, 1, 0, 1 };
  G[4] = new int[n] { 1, 1, 0, 1, 1, 1, 0 };
  G[5] = new int[n] { 0, 0, 0, 0, 1, 1, 0 };
  G[6] = new int[n] { 0, 0, 1, 1, 0, 0, 1 };

  szukaj(G, V, n);

  typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> graph_t;

  typedef std::pair<int, int> E;
  E edge_array[] = { E(0, 1), E(0, 3), E(0, 4), E(1, 2), E(1, 4), E(2, 6), E(3,
      4), E(3, 6), E(4, 5) };
  graph_t g(edge_array, edge_array + sizeof(edge_array) / sizeof(E), n);

  dfs_print_visitor vis;

  std::cout << std::endl;
  boost::depth_first_search(g, boost::visitor(vis));

  return EXIT_SUCCESS;
}
