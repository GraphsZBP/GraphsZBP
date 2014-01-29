#ifndef BOOST_DIJKSTRA_H_
#define BOOST_DIJKSTRA_H_

#include <memory>
#include "../common/graph_generator.h"
#include <boost/graph/adjacency_list.hpp>

void boost_dijkstra(std::shared_ptr<graph_generator> graph);

#endif /* BOOST_DIJKSTRA_H_ */
