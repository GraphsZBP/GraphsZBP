#include <chrono>
#include <iostream>
#include <memory>
#include <stdlib.h>

#include "common/graph_generator.h"
#include "common/random_graph_providers.h"
#include "common/statistics.h"
#include "common/measurable.h"
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
//
//void test(const std::shared_ptr<graph_generator>& graph) {
//  double duration;
//
//  std::cout << "Depth first" << std::endl;
//  duration = measure_duration(original_depth_first, graph);
//  std::cout << std::endl << "Original: " << duration << std::endl;
//  duration = measure_duration(boost_depth_first_sample, graph);
//  std::cout << std::endl << "Boost: " << duration << std::endl;
//
//  std::cout << "Breadth first" << std::endl;
//  duration = measure_duration(original_breadth_first, graph);
//  std::cout << std::endl << "Original: " << duration << std::endl;
//  duration = measure_duration(boost_breadth_first_sample, graph);
//  std::cout << std::endl << "Boost: " << duration << std::endl;
//
//  std::cout << "Floyd-Warshall" << std::endl;
//  duration = measure_duration(original_floyd_warshall, graph);
//  std::cout << std::endl << "Original: " << duration << std::endl;
//  duration = measure_duration(boost_floyd_warshall, graph);
//  std::cout << std::endl << "Boost: " << duration << std::endl;
//
//  std::cout << "Dijkstra" << std::endl;
//  duration = measure_duration(original_dijkstra, graph);
//  std::cout << std::endl << "Original: " << duration << std::endl;
//  duration = measure_duration(boost_dijkstra, graph);
//  std::cout << std::endl << "Boost: " << duration << std::endl;
//
//  std::cout << "Bellman-Ford" << std::endl;
//  duration = measure_duration(original_bellman_ford, graph);
//  std::cout << std::endl << "Original: " << duration << std::endl;
//  duration = measure_duration(boost_bellman_ford, graph);
//  std::cout << std::endl << "Boost: " << duration << std::endl;
//
//  std::cout << "Johnson" << std::endl;
//  duration = measure_duration(original_johnson, graph);
//  std::cout << std::endl << "Original: " << duration << std::endl;
//  duration = measure_duration(boost_johnson, graph);
//  std::cout << std::endl << "Boost: " << duration << std::endl;
//}

int main() {
  srand(static_cast<unsigned int>(time(NULL)));

  /*  graph_generator *generator = new graph_generator();
   std::shared_ptr<graph_generator> graph(generator);
   test(graph);


   std::cout << "Random" << std::endl;
   graph_generator *random_generator = new graph_generator(10, 90);
   std::shared_ptr<graph_generator> random_graph(random_generator);
   //random_generator->print();
   test(random_graph);
   */
  size_t sizes[] = { 1000, 2000, 5000 };
  size_t sizes_length = sizeof(sizes) / sizeof(size_t);
  size_t samples_count = 30;

  SizesWithGraphs fill_100_graphs = create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 100);
  SizesWithGraphs fill_90_graphs = create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 40);
  SizesWithGraphs map_graphs = create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 100); // TODO

  run_benchmark("Depth-First", OriginalMeasurable(original_depth_first), BoostSimpleMeasurable(boost_depth_first_sample), fill_100_graphs, fill_90_graphs,
      map_graphs, sizes, sizes_length);

  //system("pause");
  return EXIT_SUCCESS;
}
