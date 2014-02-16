#ifndef PERFORMANCE_H_
#define PERFORMANCE_H_

#include <memory>
#include <boost/function.hpp>

#include "graph_generator.h"
#include "measurable.h"

struct PerformanceResult {

  double original_duration;
  double boost_duration;

  unsigned int original_memory;
  unsigned int boost_memory;
};

typedef std::vector<std::shared_ptr<graph_generator>> GraphsCollection;

PerformanceResult measure_performance(GraphsCollection graphs, MeasurableGraphFunction original_fcn, MeasurableGraphFunction boost_fcn);

#endif /* PERFORMANCE_H_ */
