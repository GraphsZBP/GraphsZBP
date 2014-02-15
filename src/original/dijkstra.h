#ifndef ORIGINAL_DIJKSTRA_H_
#define ORIGINAL_DIJKSTRA_H_

#include <memory>
#include "../common/graph_generator.h"

void original_dijkstra(std::shared_ptr<graph_generator> graph);
bool dijkstra(graph_generator::OriginalGraph G, unsigned int source, size_t n, std::vector<double>& d);

#endif /* ORIGINAL_DIJKSTRA_H_ */
