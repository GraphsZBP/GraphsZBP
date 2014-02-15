#pragma once

#include <memory>
#include "../common/graph_generator.h"
#include "../common/graph_types.h"

void original_bellman_ford(std::shared_ptr<graph_generator> graph);
bool bellman_ford(zbp::distance_matrix G, unsigned int source, size_t n, std::vector<double>& d);
