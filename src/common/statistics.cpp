#include "statistics.h"

#include "random_graph_providers.h"

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
  SizesWithGraphs fill_90_graphs = create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 40);
  SizesWithGraphs map_graphs = create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 100); // TODO

  statistics[0] = gather_duration_statistics(fill_100_graphs, original_fcn, boost_fcn);
  statistics[1] = gather_duration_statistics(fill_90_graphs, original_fcn, boost_fcn);
  statistics[2] = gather_duration_statistics(map_graphs, original_fcn, boost_fcn);

  std::cout << std::endl << "Rozmiar,"
      "Original - 100% wype³nienia,Boost - 100% wype³nienia,"
      "Original - 90% wype³nienia,Boost - 90% wype³nienia,"
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

  run_single_memory_benchmark("100% Wype³nienia", create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 100), sizes, sizes_length);
  run_single_memory_benchmark("50% Wype³nienia", create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 50), sizes, sizes_length);
  //run_single_memory_benchmark(create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 100), sizes, sizes_length); // todo
}
