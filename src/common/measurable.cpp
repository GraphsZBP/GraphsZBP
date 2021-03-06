#include "measurable.h"

#include <chrono>
#include <algorithm>
#include <windows.h>
#include <stdio.h>
#include <psapi.h>

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

Measurement Measurable::measure(std::shared_ptr<graph_generator> graph) {
  using namespace std::chrono;
  high_resolution_clock::time_point begin = high_resolution_clock::now();

  memory_fcn(graph); // lazy graph generation

  const int DIV = 1024;

  MEMORYSTATUSEX statex;
  statex.dwLength = sizeof(statex);

  GlobalMemoryStatusEx(&statex);
  unsigned long start_free_memory = statex.ullAvailPhys / DIV;

  duration_fcn(graph);

  GlobalMemoryStatusEx(&statex);
  duration<double> time_span = duration_cast<duration<double>>(high_resolution_clock::now() - begin);
  unsigned long memory =
      start_free_memory < (statex.ullAvailPhys / DIV) ? 0 : start_free_memory - (statex.ullAvailPhys / DIV);

  Measurement result;
  result.duration = time_span.count();
  result.memory = memory;
  return result;
}

unsigned long Measurable::measure_memory(std::shared_ptr<graph_generator> graph) {
  const int DIV = 1000;

  HANDLE hProcess;
  PROCESS_MEMORY_COUNTERS pmc;
  PROCESS_MEMORY_COUNTERS pmc2;

  hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

  GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
  unsigned long start_free_memory = pmc.PeakWorkingSetSize / DIV;

  memory_fcn(graph);

  GetProcessMemoryInfo(hProcess, &pmc2, sizeof(pmc));
  unsigned long end_memory = pmc2.PeakWorkingSetSize / DIV;

  return end_memory - start_free_memory;
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

