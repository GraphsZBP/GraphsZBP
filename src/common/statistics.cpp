#include "statistics.h"

#include "graph_generator.h"
#include "map_graph_generator.h"
#include "random_graph_providers.h"
#include "../original/depth_first.h"
#include "../original/breadth_first.h"
#include "../original/floyd_warshall.h"
#include "../original/bellman_ford.h"
#include "../original/dijkstra.h"
#include "../original/johnson.h"
#include "../boost/boost_breadth_first.h"
#include "../boost/boost_depth_first.h"
#include "../boost/boost_floyd_warshall.h"
#include "../boost/boost_dijkstra.h"
#include "../boost/boost_bellman_ford.h"
#include "../boost/boost_johnson.h"

typedef std::map<unsigned int, DurationPerformanceResult> DurationStatistics;
typedef std::map<unsigned int, MemoryPerformanceResult> MemoryStatistics;

DurationStatistics gather_duration_statistics(SizesWithGraphs graphs, Measurable original_fcn, Measurable boost_fcn,
    bool include_duration = true) {
  DurationStatistics results;

  for (SizesWithGraphs::iterator it = graphs.begin(); it != graphs.end(); ++it) {
    results[it->first] = measure_performance(it->second, original_fcn, boost_fcn);
  }

  return results;
}

MemoryStatistics gather_memory_statistics(SizesWithGraphs graphs) {
  MemoryStatistics results;

  for (SizesWithGraphs::iterator it = graphs.begin(); it != graphs.end(); ++it) {
    results[it->first] = measure_memory_performance(it->second);
  }

  return results;
}

std::string duration_statistics_to_csv(size_t sizes[], size_t sizes_length,
    std::vector<DurationStatistics> statistics) {
  std::ostringstream result;
  result.precision(4);
  result << std::fixed;

  for (size_t i = 0; i < sizes_length; ++i) {
    result << sizes[i] << ",";
    for (std::vector<DurationStatistics>::iterator it = statistics.begin(); it != statistics.end(); ++it) {
      result << (*it)[sizes[i]].original_duration << "," << (*it)[sizes[i]].boost_duration << ",";
    }
    result << std::endl;
  }

  return result.str();
}

std::string memory_statistics_to_csv(size_t sizes[], size_t sizes_length, MemoryStatistics statistics) {
  std::ostringstream result;
  result << std::fixed;

  for (size_t i = 0; i < sizes_length; ++i) {
    result << sizes[i] << ",";

    result << statistics[sizes[i]].original_memory << ",";
    result << statistics[sizes[i]].boost_simple_memory << ",";
    result << statistics[sizes[i]].boost_weighed_memory << ",";
    result << statistics[sizes[i]].boost_johnson_memory << ",";

    result << std::endl;
  }

  return result.str();
}

void run_benchmark(const char* title, Measurable original_fcn, Measurable boost_fcn, size_t sizes[],
    size_t sizes_length) {
  std::vector<DurationStatistics> statistics(3);
  size_t samples_count = 5;

  std::cout << title << std::endl;

  SizesWithGraphs fill_100_graphs = create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 100);
  SizesWithGraphs fill_90_graphs = create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 50);
  SizesWithGraphs map_graphs = create_map_graphs_for_sizes(sizes, sizes_length, samples_count, 100, 15);

  statistics[0] = gather_duration_statistics(fill_100_graphs, original_fcn, boost_fcn);
  statistics[1] = gather_duration_statistics(fill_90_graphs, original_fcn, boost_fcn);
  statistics[2] = gather_duration_statistics(map_graphs, original_fcn, boost_fcn);

  std::cout << std::endl << "Rozmiar,"
      "Original - 100% wype³nienia,Boost - 100% wype³nienia,"
      "Original - 50% wype³nienia,Boost - 50% wype³nienia,"
      "Original - mapa,Boost - mapa," << std::endl;

  std::cout << duration_statistics_to_csv(sizes, sizes_length, statistics);
}

void run_single_memory_benchmark(const char* title, SizesWithGraphs graphs, size_t sizes[], size_t sizes_length) {
  MemoryStatistics statistics;

  std::cout << title << std::endl;

  statistics = gather_memory_statistics(graphs);

  std::cout << std::endl << "Rozmiar,"
      "Original,Boost - adjacency_matrix,"
      "Boost - adjacency_list 1,Boost - adjacency_list 2" << std::endl;

  std::cout << memory_statistics_to_csv(sizes, sizes_length, statistics);
}

void run_memory_benchmark(size_t sizes[], size_t sizes_length) {
  std::vector<MemoryStatistics> statistics(3);
  size_t samples_count = 5;

  run_single_memory_benchmark("100% Wype³nienia",
      create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 100), sizes, sizes_length);
  run_single_memory_benchmark("50% Wype³nienia", create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 50),
      sizes, sizes_length);
  run_single_memory_benchmark("Mapa", create_map_graphs_for_sizes(sizes, sizes_length, samples_count, 100, 15), sizes,
      sizes_length);
}

/*
void general_memory_benchmark() {
  size_t sizes[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000 }; //, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000  };
  size_t sizes_length = sizeof(sizes) / sizeof(size_t);

  run_memory_benchmark(sizes, sizes_length);
}
*/

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

void general_memory_benchmark(char** argv) {
  graph_generator* random_generator;
  if (argv[3][0] == 'm') {
    random_generator = new map_graph_generator(atoi(argv[2]), 100, 15);
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

