#include "measurable.h"

#include <chrono>
#include <algorithm>
#include <windows.h>

void measure_original_memory(std::shared_ptr<graph_generator> graph) {
  graph->original_graph();
}

void measure_boost_simple_memory(std::shared_ptr<graph_generator> graph) {
  graph->boost_graph();
}

void measure_boost_weighted_graph(std::shared_ptr<graph_generator> graph) {
  graph->boost_weighted_graph();
}

void measure_boost_johnson_graph(std::shared_ptr<graph_generator> graph) {
  graph->boost_johnson_graph();
}

Measurable::Measurable(GraphFunction duration_fcn, GraphFunction memory_fcn) :
    duration_fcn(duration_fcn), memory_fcn(memory_fcn) {
}

double Measurable::measure_duration(std::shared_ptr<graph_generator> graph) {
  using namespace std::chrono;
  high_resolution_clock::time_point begin = high_resolution_clock::now();

  duration_fcn(graph);

  duration<double> time_span = duration_cast<duration<double>>(high_resolution_clock::now() - begin);
  return time_span.count();
}

unsigned long Measurable::measure_memory(std::shared_ptr<graph_generator> graph) {
  const int DIV = 1024;

  MEMORYSTATUSEX statex;
  statex.dwLength = sizeof(statex);

  GlobalMemoryStatusEx(&statex);
  unsigned long start_free_memory = statex.ullAvailPhys / DIV;
  memory_fcn(graph);

  GlobalMemoryStatusEx(&statex);

  return start_free_memory < (statex.ullAvailPhys / DIV) ? 0 : start_free_memory - (statex.ullAvailPhys / DIV);
}

OriginalMeasurable::OriginalMeasurable(GraphFunction duration_fcn) :
    Measurable(duration_fcn, measure_original_memory) {
}

BoostSimpleMeasurable::BoostSimpleMeasurable(GraphFunction duration_fcn) :
    Measurable(duration_fcn, measure_boost_simple_memory) {
}

BoostWeightedGraphMeasurable::BoostWeightedGraphMeasurable(GraphFunction duration_fcn) :
    Measurable(duration_fcn, measure_boost_weighted_graph) {
}

BoostJohnsonGraphMeasurable::BoostJohnsonGraphMeasurable(GraphFunction duration_fcn) :
    Measurable(duration_fcn, measure_boost_johnson_graph) {
}

