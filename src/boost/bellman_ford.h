/*
 * bellmanford.h
 *
 *  Created on: 29 sty 2014
 *      Author: Micha³
 */

#ifndef BELLMANFORD_H_
#define BELLMANFORD_H_

#include <memory>
#include "../common/graph_generator.h"
#include <boost/graph/adjacency_list.hpp>

void boost_bellman_ford(std::shared_ptr<graph_generator> graph);

#endif /* BELLMANFORD_H_ */
