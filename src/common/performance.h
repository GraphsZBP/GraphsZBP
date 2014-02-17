#ifndef PERFORMANCE_H_
#define PERFORMANCE_H_

#include <memory>
#include <boost/function.hpp>

#include "graph_generator.h"
#include "measurable.h"

struct DurationPerformanceResult {

  double original_duration;
  double boost_duration;

  unsigned int original_memory;
  unsigned int boost_memory;
};

struct MemoryPerformanceResult {

  unsigned long original_memory;
  unsigned long boost_simple_memory;
  unsigned long boost_weighed_memory;
  unsigned long boost_johnson_memory;
};

typedef std::vector<std::shared_ptr<graph_generator>> GraphsCollection;

DurationPerformanceResult measure_performance(GraphsCollection graphs, Measurable original_fcn, Measurable boost_fcn);
MemoryPerformanceResult measure_memory_performance(GraphsCollection graphs);

#endif /* PERFORMANCE_H_ */
