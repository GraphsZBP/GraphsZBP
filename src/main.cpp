#include <chrono>
#include <iostream>
#include <memory>
#include <stdlib.h>

#include "common/graph_generator.h"
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

void general_duration_benchmark() {
  size_t small[] = { 100, 200, 500 };
  size_t medium[] = { 500, 750, 1000 };
  size_t large[] = { 1000, 2000, 5000 };
  size_t sizes_length = sizeof(medium) / sizeof(size_t);

  run_benchmark("Depth-First", OriginalMeasurable(original_depth_first), BoostSimpleMeasurable(boost_depth_first),
      large, sizes_length);
  run_benchmark("Breadth-First", OriginalMeasurable(original_breadth_first), BoostSimpleMeasurable(boost_breadth_first),
      large, sizes_length);
  run_benchmark("Floyd-Warshall", OriginalMeasurable(original_floyd_warshall),
      BoostWeightedGraphMeasurable(boost_floyd_warshall), small, sizes_length);
  run_benchmark("Dijkstra", OriginalMeasurable(original_dijkstra), BoostWeightedGraphMeasurable(boost_dijkstra), medium,
      sizes_length);
  run_benchmark("Bellman-Ford", OriginalMeasurable(original_bellman_ford),
      BoostWeightedGraphMeasurable(boost_bellman_ford), medium, sizes_length);
  run_benchmark("Johnson", OriginalMeasurable(original_johnson), BoostJohnsonGraphMeasurable(boost_johnson), small,
      sizes_length);
}

void general_memory_benchmark() {
  size_t sizes[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000 }; //, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000  };
  size_t sizes_length = sizeof(sizes) / sizeof(size_t);

  run_memory_benchmark(sizes, sizes_length);
}

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

int main(int argc, char **argv) {
  srand(static_cast<unsigned int>(time(NULL)));

  if (argc == 4) {
    graph_generator* random_generator;
    if (argv[3][0] == 'm') {
      random_generator = NULL; // TODO mapa
    } else {
      random_generator = new graph_generator(atoi(argv[2]), atoi(argv[3]));
    }

    std::shared_ptr<graph_generator> graph(random_generator);

    switch (argv[1][0]) {
    case 'o':
      std::cout << OriginalMeasurable(original_breadth_first).measure_memory(graph);
      break;
    case 's':
      graph->original_graph();
      std::cout << BoostSimpleMeasurable(original_breadth_first).measure_memory(graph);
      break;
    case 'w':
      graph->original_graph();
      std::cout << BoostWeightedGraphMeasurable(original_breadth_first).measure_memory(graph);
      break;
    case 'j':
      graph->original_graph();
      std::cout << BoostJohnsonGraphMeasurable(original_breadth_first).measure_memory(graph);
      break;
    }
  } else {
    general_duration_benchmark();
  }

  /*  graph_generator *generator = new graph_generator();
   std::shared_ptr<graph_generator> graph(generator);
   test(graph);


   std::cout << "Random" << std::endl;
   graph_generator *random_generator = new graph_generator(10, 90);
   std::shared_ptr<graph_generator> random_graph(random_generator);
   //random_generator->print();
   test(random_graph);
   */
//system("pause");
  return EXIT_SUCCESS;
}
