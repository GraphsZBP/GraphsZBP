#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "performance.h"

typedef std::map<unsigned int, GraphsCollection> SizesWithGraphs;

void run_benchmark(const char* title, MeasurableGraphFunction original_fcn, MeasurableGraphFunction boost_fcn,
    size_t sizes[], size_t sizes_length);

#endif /* STATISTICS_H_ */
