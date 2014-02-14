/*
 * johnson.h
 *
 *  Created on: 29 sty 2014
 *      Author: Micha³
 */

#ifndef BOOST_JOHNSON_H_
#define BOOST_JOHNSON_H_

#include <memory>
#include "../common/graph_generator.h"
#include <boost/graph/adjacency_list.hpp>

void boost_johnson(std::shared_ptr<graph_generator> graph);

#endif /* JOHNSON_H_ */
