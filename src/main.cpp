#include <chrono>
#include <iostream>
#include <memory>
#include <stdlib.h>

#include "common/graph_generator.h"
#include "original/depth_first.h"
#include "boost/depth_first.h"
#include "original/breadth_first.h"
#include "boost/breadth_first.h"

void test(const std::shared_ptr<graph_generator>& graph) {
  using namespace std::chrono;

  high_resolution_clock::time_point begin;
  duration<double> time_span;

  std::cout << "Depth first" << std::endl;

  begin = high_resolution_clock::now();
  original_depth_first_sample(graph);
  time_span = duration_cast<duration<double>>(high_resolution_clock::now() - begin);
  std::cout << std::endl << time_span.count() << std::endl;

  begin = high_resolution_clock::now();
  boost_depth_first_sample(graph);
  time_span = duration_cast<duration<double>>(high_resolution_clock::now() - begin);
  std::cout << std::endl << time_span.count() << std::endl;

  std::cout << std::endl << "Breadth first" << std::endl;
  begin = high_resolution_clock::now();
  original_breadth_first_sample(graph);
  time_span = duration_cast<duration<double>>(high_resolution_clock::now() - begin);
  std::cout << std::endl << time_span.count() << std::endl;

  begin = high_resolution_clock::now();
  boost_breadth_first_sample(graph);
  time_span = duration_cast<duration<double>>(high_resolution_clock::now() - begin);
  std::cout << std::endl << time_span.count() << std::endl;
}

int main() {
  srand(static_cast<unsigned int>(time(NULL)));
  graph_generator *generator = new graph_generator();
  std::shared_ptr<graph_generator> graph(generator);
  test(graph);

  std::cout << "Random" << std::endl;
  graph_generator *random_generator = new graph_generator(5000, 90);
  std::shared_ptr<graph_generator> random_graph(random_generator);
  //random_generator->print();
  test(random_graph);

  return EXIT_SUCCESS;
}
