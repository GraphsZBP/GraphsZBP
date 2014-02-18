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

void demo(const std::shared_ptr<graph_generator>& graph) {
  double duration;

  std::cout << "Depth first" << std::endl;
  duration = OriginalMeasurable(original_depth_first).measure(graph).duration;
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostSimpleMeasurable(boost_depth_first).measure(graph).duration;
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Breadth first" << std::endl;
  duration = OriginalMeasurable(original_breadth_first).measure(graph).duration;
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostSimpleMeasurable(boost_breadth_first).measure(graph).duration;
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Floyd-Warshall" << std::endl;
  duration = OriginalMeasurable(original_floyd_warshall).measure(graph).duration;
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostWeightedGraphMeasurable(boost_floyd_warshall).measure(graph).duration;
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Dijkstra" << std::endl;
  duration = OriginalMeasurable(original_dijkstra).measure(graph).duration;
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostWeightedGraphMeasurable(boost_dijkstra).measure(graph).duration;
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Bellman-Ford" << std::endl;
  duration = OriginalMeasurable(original_bellman_ford).measure(graph).duration;
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostWeightedGraphMeasurable(boost_bellman_ford).measure(graph).duration;
  std::cout << std::endl << "Boost: " << duration << std::endl;

  std::cout << "Johnson" << std::endl;
  duration = OriginalMeasurable(original_johnson).measure(graph).duration;
  std::cout << std::endl << "Original: " << duration << std::endl;
  duration = BoostJohnsonGraphMeasurable(boost_johnson).measure(graph).duration;
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
  graph_generator* random_generator = new map_graph_generator(20, 100, 4);
  std::shared_ptr<graph_generator> random_graph(random_generator);
  demo(random_graph);
}

int main(int argc, char **argv) {
  srand(static_cast<unsigned int>(time(NULL)));

  if (argc == 4) {
    general_memory_benchmark(argv);
  } else {
    demo_dummy();
    //print_sample_graphs();
    //general_duration_benchmark();
  }

//system("pause");
  return EXIT_SUCCESS;
}
