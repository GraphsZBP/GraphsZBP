#include "timer.h"

#include <chrono>

double measure(boost::function<void(std::shared_ptr<graph_generator>)> f,
    const std::shared_ptr<graph_generator>& graph) {

  using namespace std::chrono;
  high_resolution_clock::time_point begin = high_resolution_clock::now();

  f(graph);

  duration<double> time_span = duration_cast<duration<double>>(high_resolution_clock::now() - begin);
  return time_span.count();
}
