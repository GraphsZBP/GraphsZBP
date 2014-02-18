#pragma once
#include "K:\Projekty\GraphsZbp\src\common\graph_generator.h"
class map_graph_generator :
	public graph_generator
{
public:
	map_graph_generator();
	map_graph_generator(size_t size, int fill);
	~map_graph_generator();
	zbp::distance_matrix original_graph();
};

