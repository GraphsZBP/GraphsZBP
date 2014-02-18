#include <chrono>
#include <iostream>
#include <memory>
#include <stdlib.h>

#include "common/graph_generator.h"
#include "common/map_graph_generator.h"
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

void demo(const std::shared_ptr<graph_generator>& graph) {
  double duration;

  std::cout << "Depth first" << std::endl;
  duration = OriginalMeasurable(original_depth_first).measure_duration(graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostSimpleMeasurable(boost_depth_first).measure_duration(graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Breadth first" << std::endl;
  duration = OriginalMeasurable(original_breadth_first).measure_duration(graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostSimpleMeasurable(boost_breadth_first).measure_duration(graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Floyd-Warshall" << std::endl;
  duration = OriginalMeasurable(original_floyd_warshall).measure_duration(graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostWeightedGraphMeasurable(boost_floyd_warshall).measure_duration(graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Dijkstra" << std::endl;
  duration = OriginalMeasurable(original_dijkstra).measure_duration(graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostWeightedGraphMeasurable(boost_dijkstra).measure_duration(graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Bellman-Ford" << std::endl;
  duration = OriginalMeasurable(original_bellman_ford).measure_duration(graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostWeightedGraphMeasurable(boost_bellman_ford).measure_duration(graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Johnson" << std::endl;
  duration = OriginalMeasurable(original_johnson).measure_duration(graph);
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostJohnsonGraphMeasurable(boost_johnson).measure_duration(graph);
  std::cout << std::endl << "Boost: " << duration << std::endl;
}

void print_sample_graphs() {
  int size = 10;
  graph_generator* random_generator = new graph_generator(size, 100);
  random_generator->original_graph();
  random_generator->print();
  delete random_generator;
  std::cout << std::endl;

  random_generator = new graph_generator(size, 50);
  random_generator->original_graph();
  random_generator->print();
  delete random_generator;
  std::cout << std::endl;

  random_generator = new map_graph_generator(size, 100, 4);
  random_generator->original_graph();
  random_generator->print();
  delete random_generator;
}

void general_memory_benchmark(char** argv) {
  graph_generator* random_generator;
  if (argv[3][0] == 'm') {
    random_generator = new map_graph_generator(atoi(argv[2]), 100, 10);
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
}

void demo_dummy() {
  graph_generator* generator = new graph_generator();
  std::shared_ptr<graph_generator> graph(generator);
  demo(graph);
}

void demo_filled() {
  graph_generator* random_generator = new graph_generator(10, 90);
  std::shared_ptr<graph_generator> random_graph(random_generator);
  demo(random_graph);
}

void demo_map() {
  graph_generator* random_generator = new map_graph_generator(10, 100, 4);
  std::shared_ptr<graph_generator> random_graph(random_generator);
  demo(random_graph);
}

int main(int argc, char **argv) {
  srand(static_cast<unsigned int>(time(NULL)));

  if (argc == 4) {
    general_memory_benchmark(argv);
  } else {
    demo_map();
    //print_sample_graphs();
    //general_duration_benchmark();
  }

  std::cout << "Random" << std::endl;
  demo_filled();
//system("pause");
  return EXIT_SUCCESS;
}
