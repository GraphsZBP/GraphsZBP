#include <iostream>
#include <memory>
#include <stdlib.h>

#include "common/graph_generator.h"
#include "original/depth_first.h"
#include "boost/depth_first.h"
#include "original/breadth_first.h"
#include "boost/breadth_first.h"

int main() {
  graph_generator *generator = new graph_generator();
  std::shared_ptr<graph_generator> graph(generator);

  std::cout << "Depth first" << std::endl;
  original_depth_first_sample(graph);
  std::cout << std::endl;
  boost_depth_first_sample(graph);

  std::cout << std::endl << "Breadth first" << std::endl;
  original_breadth_first_sample(graph);
  std::cout << std::endl;
  boost_breadth_first_sample(graph);

  return EXIT_SUCCESS;
}
