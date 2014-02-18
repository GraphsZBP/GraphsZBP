#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "performance.h"

typedef std::map<unsigned int, GraphsCollection> SizesWithGraphs;

void general_duration_benchmark();
void general_memory_benchmark(char** argv);

#endif /* STATISTICS_H_ */
