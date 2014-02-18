#include "performance.h"

#include "../original/breadth_first.h"

DurationPerformanceResult measure_performance(GraphsCollection graphs, Measurable original_fcn,
    Measurable boost_fcn) {
  int tests_performed = 0;

  unsigned long original_memory = 0;
  unsigned long boost_memory = 0;
  double original_duration = 0;
  double boost_duration = 0;
  Measurement measurement;

  for (unsigned int i = 0; i < graphs.size(); ++i) {
    graphs[i]->free_all_memory();

    measurement = original_fcn.measure(graphs[i]);
    original_duration = measurement.duration;
    original_memory += measurement.memory;

    measurement = boost_fcn.measure(graphs[i]);
    boost_duration = measurement.duration;
    boost_memory += measurement.memory;

    graphs[i]->free_all_memory();

    std::cout << "." << std::flush;
    if (tests_performed++ == 80) {
      tests_performed = 0;
      std::cout << std::endl;
    }
  }

  DurationPerformanceResult result;
  result.original_memory = original_memory / static_cast<double>(graphs.size());
  result.boost_memory = boost_memory / static_cast<double>(graphs.size());
  result.original_duration = original_duration / static_cast<double>(graphs.size());
  result.boost_duration = boost_duration / static_cast<double>(graphs.size());

  return result;
}

MemoryPerformanceResult measure_memory_performance(GraphsCollection graphs) {
  int tests_performed = 0;

  unsigned long original_memory = 0;
  unsigned long boost_simple_memory = 0;
  unsigned long boost_weighed_memory = 0;
  unsigned long boost_johnson_memory = 0;

  for (unsigned int i = 0; i < graphs.size(); ++i) {
    graphs[i]->free_all_memory();

    original_memory += OriginalMeasurable(original_breadth_first).measure_memory(graphs[i]);
    boost_simple_memory += BoostSimpleMeasurable(original_breadth_first).measure_memory(graphs[i]);
    graphs[i]->free_boost_memory();
    boost_weighed_memory += BoostWeightedGraphMeasurable(original_breadth_first).measure_memory(graphs[i]);
    graphs[i]->free_boost_memory();
    boost_johnson_memory += BoostJohnsonGraphMeasurable(original_breadth_first).measure_memory(graphs[i]);

    graphs[i]->free_all_memory();

    std::cout << "." << std::flush;
    if (tests_performed++ == 80) {
      tests_performed = 0;
      std::cout << std::endl;
    }
  }

  MemoryPerformanceResult result;
  result.original_memory = original_memory / graphs.size();
  result.boost_simple_memory = boost_simple_memory / graphs.size();
  result.boost_weighed_memory = boost_weighed_memory / graphs.size();
  result.boost_johnson_memory = boost_johnson_memory / graphs.size();

  return result;
}
