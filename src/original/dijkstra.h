#pragma once

#include <memory>
#include "../common/graph_generator.h"

void original_dijkstra(std::shared_ptr<graph_generator> graph);
bool dijkstra(zbp::distance_matrix G, unsigned int source, size_t n, std::vector<double>& d);
