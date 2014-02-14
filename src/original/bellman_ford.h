#ifndef ORIGINAL_BELLMAN_FORD_H
#define ORIGINAL_BELLMAN_FORD_H

#include <memory>
#include "../common/graph_generator.h"

void original_bellman_ford(std::shared_ptr<graph_generator> graph);
bool bellman_ford(graph_generator::OriginalGraph G, unsigned int source, size_t n, std::vector<double>& d);

#endif /* ORIGINAL_BELLMAN_FORD_H */
