#ifndef PERFORMANCE_H_
#define PERFORMANCE_H_

#include <memory>
#include <boost/function.hpp>

#include "graph_generator.h"

struct PerformanceResult {

  double depth_first;
  double breadth_first;
  double floyd_warshall;
  double bellman_ford;
  double dijkstra;
  double johnson;
};

typedef boost::function<std::shared_ptr<graph_generator>(unsigned int)> GraphProvider;
typedef boost::function<PerformanceResult(std::shared_ptr<graph_generator>)> PerformanceMeasurer;
typedef std::vector<std::shared_ptr<graph_generator>> GraphsCollection;

PerformanceResult measure_original_performance(const std::shared_ptr<graph_generator> graph);
PerformanceResult measure_boost_performance(const std::shared_ptr<graph_generator> graph);
PerformanceResult average_results(std::vector<PerformanceResult> test_results);

#endif /* PERFORMANCE_H_ */
