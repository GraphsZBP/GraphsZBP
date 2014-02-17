#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "performance.h"

typedef std::map<unsigned int, GraphsCollection> SizesWithGraphs;

void run_benchmark(const char* title, Measurable original_fcn, Measurable boost_fcn, size_t sizes[],
    size_t sizes_length);
void run_memory_benchmark(size_t sizes[], size_t sizes_length);

#endif /* STATISTICS_H_ */
