#include <chrono>
#include <iostream>
#include <memory>
#include <stdlib.h>

#include "common/graph_generator.h"
#include "common/timer.h"
#include "original/depth_first.h"
#include "boost/depth_first.h"
#include "original/breadth_first.h"
#include "boost/breadth_first.h"
#include "original/floyd_warshall.h"
#include "boost/floyd_warshall.h"
#include "boost/dijkstra.h"
#include "boost/bellman_ford.h"
#include "boost/johnson.h"
#include "original/dijkstra.h"


void test(const std::shared_ptr<graph_generator>& graph) {
  double duration;

  std::cout << "Depth first" << std::endl;
  duration = measure(&original_depth_first_sample, graph);
  std::cout << std::endl << duration << std::endl;
  duration = measure(&boost_depth_first_sample, graph);
  std::cout << std::endl << duration << std::endl;

  std::cout << "Breadth first" << std::endl;
  duration = measure(&original_breadth_first_sample, graph);
  std::cout << std::endl << duration << std::endl;
  duration = measure(&boost_breadth_first_sample, graph);
  std::cout << std::endl << duration << std::endl;

  std::cout << "Floyd-Warshall" << std::endl;
  duration = measure(&original_floyd_warshall, graph);
  std::cout << std::endl << duration << std::endl;
  duration = measure(&boost_floyd_warshall, graph);
  std::cout << std::endl << duration << std::endl;

  std::cout << "Dijkstra" << std::endl;
  //duration = measure(&original_dijkstra, graph);
  //std::cout << std::endl << duration << std::endl;
  duration = measure(&boost_dijkstra, graph);
  std::cout << std::endl << duration << std::endl;

  std::cout << "Bellman-Ford" << std::endl;
  //duration = measure(&, graph);
  //std::cout << std::endl << duration << std::endl;
  duration = measure(&boost_bellman_ford, graph);
  std::cout << std::endl << duration << std::endl;

  std::cout << "Johnson" << std::endl;
  //duration = measure(&, graph);
  //std::cout << std::endl << duration << std::endl;
  duration = measure(&boost_johnson, graph);
  std::cout << std::endl << duration << std::endl;
}

int main() {
  srand(static_cast<unsigned int>(time(NULL)));

  graph_generator *generator = new graph_generator();
  std::shared_ptr<graph_generator> graph(generator);
  test(graph);

/*
  std::cout << "Random" << std::endl;
  graph_generator *random_generator = new graph_generator(1000, 90);
  std::shared_ptr<graph_generator> random_graph(random_generator);
  //random_generator->print();
  test(random_graph);
*/

  return EXIT_SUCCESS;
}
