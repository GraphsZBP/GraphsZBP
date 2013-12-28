#include <iostream>
#include <stdlib.h>

#include "original/depth_first.h"
#include "boost/depth_first.h"

int main() {
  original_depth_first_sample();
  std::cout << std::endl;
  boost_depth_first_sample();

  return EXIT_SUCCESS;
}
