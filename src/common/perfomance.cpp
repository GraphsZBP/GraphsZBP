#include "performance.h"

#include "timer.h"
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

PerformanceResult measure_original_performance(const std::shared_ptr<graph_generator> graph) {
  PerformanceResult result;

  result.depth_first = measure(original_depth_first, graph);
  result.breadth_first = measure(original_breadth_first, graph);
  result.floyd_warshall = measure(original_floyd_warshall, graph);
  result.dijkstra = measure(original_dijkstra, graph);
  result.bellman_ford = measure(original_bellman_ford, graph);
  result.johnson = measure(original_johnson, graph);

  return result;
}

PerformanceResult measure_boost_performance(const std::shared_ptr<graph_generator> graph) {
  PerformanceResult result;

  result.depth_first = measure(boost_depth_first_sample, graph);
  result.breadth_first = measure(boost_breadth_first_sample, graph);
  result.floyd_warshall = measure(boost_floyd_warshall, graph);
  result.dijkstra = measure(boost_dijkstra, graph);
  result.bellman_ford = measure(boost_bellman_ford, graph);
  result.johnson = measure(boost_johnson, graph);

  return result;
}

PerformanceResult average_results(std::vector<PerformanceResult> test_results) {
  PerformanceResult average;

  for (std::vector<PerformanceResult>::iterator i = test_results.begin(); i != test_results.end(); ++i) {
    average.depth_first += i->depth_first;
    average.breadth_first += i->breadth_first;
    average.floyd_warshall += i->floyd_warshall;
    average.dijkstra += i->dijkstra;
    average.bellman_ford += i->bellman_ford;
    average.johnson += i->johnson;
  }

  average.depth_first /= test_results.size();
  average.breadth_first /= test_results.size();
  average.floyd_warshall /= test_results.size();
  average.dijkstra /= test_results.size();
  average.bellman_ford /= test_results.size();
  average.johnson /= test_results.size();

  return average;
}
