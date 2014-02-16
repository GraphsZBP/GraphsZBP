#include "performance.h"

void track_tests() {
  static int tests_performed = 0;

  std::cout << "." << std::flush;
  if (tests_performed++ == 80) {
    tests_performed = 0;
    std::cout << std::endl;
  }
}

PerformanceResult measure_performance(GraphsCollection graphs, MeasurableGraphFunction original_fcn,
    MeasurableGraphFunction boost_fcn) {
  double original_duration = 0;
  double boost_duration = 0;
  unsigned long original_memory = 0;
  unsigned long boost_memory = 0;

  for (unsigned int i = 0; i < graphs.size(); ++i) {
    Measurement original_measurement = original_fcn(graphs[i]);
    Measurement boost_measurement = boost_fcn(graphs[i]);

    original_duration += original_measurement.duration;
    original_memory += original_measurement.memory;
    boost_duration += boost_measurement.duration;
    boost_memory += boost_measurement.memory;

    graphs[i]->reset();

    track_tests();
  }

  PerformanceResult result;
  result.original_duration = original_duration / static_cast<double>(graphs.size());
  result.original_memory = original_memory / static_cast<double>(graphs.size());
  result.boost_duration = boost_duration / static_cast<double>(graphs.size());
  result.boost_memory = boost_memory / static_cast<double>(graphs.size());

  return result;
}
