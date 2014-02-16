#include <chrono>
#include <iostream>
#include <memory>
#include <stdlib.h>

#include "common/graph_generator.h"
#include "common/timer.h"
#include "original/depth_first.h"
#include "original/breadth_first.h"
#include "original/floyd_warshall.h"
#include "original/bellman_ford.h"
#include "original/dijkstra.h"
#include "original/johnson.h"
#include "boost/boost_breadth_first.h"
#include "boost/boost_depth_first.h"
#include "boost/boost_floyd_warshall.h"
#include "boost/boost_dijkstra.h"
#include "boost/boost_bellman_ford.h"
#include "boost/boost_johnson.h"

void test(const std::shared_ptr<graph_generator>& graph) {
  double duration;
 
  std::cout << "Depth first" << std::endl;
  duration = measure(original_depth_first, graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = measure(boost_depth_first_sample, graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;
  
  std::cout << "Breadth first" << std::endl;
  duration = measure(original_breadth_first, graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = measure(boost_breadth_first_sample, graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Floyd-Warshall" << std::endl;
  duration = measure(original_floyd_warshall, graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = measure(boost_floyd_warshall, graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Dijkstra" << std::endl;
  duration = measure(original_dijkstra, graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = measure(boost_dijkstra, graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Bellman-Ford" << std::endl;
  duration = measure(original_bellman_ford, graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = measure(boost_bellman_ford, graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Johnson" << std::endl;
  duration = measure(original_johnson, graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = measure(boost_johnson, graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;
}

int main() {
  srand(static_cast<unsigned int>(time(NULL)));

  graph_generator *generator = new graph_generator();
  std::shared_ptr<graph_generator> graph(generator);
  test(graph);


  std::cout << "Random" << std::endl;
  graph_generator *random_generator = new graph_generator(10, 90);
  std::shared_ptr<graph_generator> random_graph(random_generator);
  //random_generator->print();
  test(random_graph);

  std::vector<Statistics> results = run_90_fill_tests();

  for (std::vector<Statistics>::iterator i = results.begin(); i != results.end(); ++i) {
    std::cout << i->size << "," << i->original_result << "," << i->boost_result;
  }

  system("pause");
  return EXIT_SUCCESS;
}
