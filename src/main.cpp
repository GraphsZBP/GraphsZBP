#include <iostream>
#include <stdlib.h>

#include "original/depth_first.h"
#include "boost/depth_first.h"
#include "original/breadth_first.h"
#include "boost/breadth_first.h"

int main() {
  std::cout << "Depth first" << std::endl;
  original_depth_first_sample();
  std::cout << std::endl;
  boost_depth_first_sample();

  std::cout << std::endl << "Breadth first" << std::endl;
  original_breadth_first_sample();
  std::cout << std::endl;
  boost_breadth_first_sample();

  return EXIT_SUCCESS;
}
