#include "statistics.h"

GraphsCollection generate_random_graphs(unsigned int repeats, int size, int fill) {
  GraphsCollection graphs(repeats);

  for (unsigned int i = 0; i < repeats; ++i) {
    graph_generator* random_generator = new graph_generator(size, fill);
    graphs[i] = std::shared_ptr<graph_generator>(random_generator);
  }

  return graphs;
}

Statistics gather_statistics(unsigned int repeats, const GraphsCollection& graphs, int size) {
  std::vector<PerformanceResult> original_results(repeats);
  std::vector<PerformanceResult> boost_results(repeats);

  for (unsigned int i = 0; i < repeats; ++i) {
    original_results[i] = measure_original_performance(graphs[i]);
    boost_results[i] = measure_boost_performance(graphs[i]);
  }

  Statistics statistics;
  statistics.size = size;
  statistics.original_result = average_results(original_results);
  statistics.boost_result = average_results(boost_results);

  return statistics;
}

std::vector<Statistics> run_90_fill_tests() {
  unsigned int samples_count = 3;
  int sizes[] = { 10, 20, 30 };
  int fill = 90;
  
  std::vector<Statistics> results(sizeof(sizes));
  for (unsigned int i = 0; i < sizeof(sizes); ++i) {
    GraphsCollection graphs = generate_random_graphs(samples_count, sizes[i], fill);
    results[i] = gather_statistics(samples_count, graphs, sizes[i]);
  }

  return results;
}
