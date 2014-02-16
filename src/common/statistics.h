#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "performance.h"

struct Statistics {
  unsigned int size;
  PerformanceResult original_result;
  PerformanceResult boost_result;
};

std::vector<Statistics> run_90_fill_tests();

#endif /* STATISTICS_H_ */
