#include "statistics.h"

#include "random_graph_providers.h"

typedef std::map<unsigned int, PerformanceResult> Statistics;

Statistics gather_statistics(SizesWithGraphs graphs, MeasurableGraphFunction original_fcn, MeasurableGraphFunction boost_fcn) {
  Statistics results;

  for (SizesWithGraphs::iterator it = graphs.begin(); it != graphs.end(); ++it) {
    results[it->first] = measure_performance(it->second, original_fcn, boost_fcn);
  }

  return results;
}

std::string statistics_to_csv(size_t sizes[], size_t sizes_length, std::vector<Statistics> statistics) {
  std::ostringstream result;
  result.precision(4);
  result << std::fixed;

  for (size_t i = 0; i < sizes_length; ++i) {
    result << sizes[i] << ",";
    for (std::vector<Statistics>::iterator it = statistics.begin(); it != statistics.end(); ++it) {
      result << (*it)[sizes[i]].original_duration << "," << (*it)[sizes[i]].boost_duration << ",";
    }
    for (std::vector<Statistics>::iterator it = statistics.begin(); it != statistics.end(); ++it) {
      result << (*it)[sizes[i]].original_memory << "," << (*it)[sizes[i]].boost_memory << ",";
    }
    result << std::endl;
  }

  return result.str();
}

void run_benchmark(const char* title, MeasurableGraphFunction original_fcn, MeasurableGraphFunction boost_fcn,
    size_t sizes[], size_t sizes_length) {
  std::vector<Statistics> statistics(3);
  size_t samples_count = 5;

  std::cout << title << std::endl;

  SizesWithGraphs fill_100_graphs = create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 100);
  SizesWithGraphs fill_90_graphs = create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 40);
  SizesWithGraphs map_graphs = create_filled_graphs_for_sizes(sizes, sizes_length, samples_count, 100); // TODO

  statistics[0] = gather_statistics(fill_100_graphs, original_fcn, boost_fcn);
  statistics[1] = gather_statistics(fill_90_graphs, original_fcn, boost_fcn);
  statistics[2] = gather_statistics(map_graphs, original_fcn, boost_fcn);

  std::cout << std::endl << "Rozmiar,"
      "Original - 100% wype�nienia,Boost - 100% wype�nienia,"
      "Original - 90% wype�nienia,Boost - 90% wype�nienia,"
      "Original - mapa,Boost - mapa,"
      "Original - 100% wype�nienia - pami��,Boost - 100% wype�nienia - pami��,"
      "Original - 90% wype�nienia - pami��,Boost - 90% wype�nienia - pami��,"
      "Original - mapa - pami��,Boost - mapa - pami��," << std::endl;

  std::cout << statistics_to_csv(sizes, sizes_length, statistics);
}
