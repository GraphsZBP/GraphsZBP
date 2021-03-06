#ifndef RANDOM_GRAPH_PROVIDERS_H_
#define RANDOM_GRAPH_PROVIDERS_H_

#include "statistics.h"

SizesWithGraphs create_filled_graphs_for_sizes(size_t sizes[], size_t sizes_length, size_t samples_count,
    unsigned short fill);
SizesWithGraphs create_map_graphs_for_sizes(size_t sizes[], size_t sizes_length, size_t samples_count,
    unsigned short fill, unsigned short neighbourhood);

#endif /* RANDOM_GRAPH_PROVIDERS_H_ */
