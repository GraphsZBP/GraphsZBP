#ifndef MAP_GRAPH_GENERATOR_H_
#define MAP_GRAPH_GENERATOR_H_

#include "graph_generator.h"

class map_graph_generator : public graph_generator
{
  unsigned int m_neighbourhood_size;
public:
	map_graph_generator(size_t size, int fill, unsigned int neighbourhood_size);
	virtual ~map_graph_generator();
	zbp::distance_matrix original_graph();
};

#endif /* MAP_GRAPH_GENERATOR_H_ */
