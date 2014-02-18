#include "random_graph_providers.h"

#include "graph_generator.h"
#include "map_graph_generator.h"

GraphsCollection generate_filled_graphs(unsigned int repeats, int size, int fill) {
  GraphsCollection graphs(repeats);

  for (unsigned int i = 0; i < repeats; ++i) {
    graph_generator* random_generator = new graph_generator(size, fill);
    graphs[i] = std::shared_ptr<graph_generator>(random_generator);
  }

  return graphs;
}

SizesWithGraphs create_filled_graphs_for_sizes(size_t sizes[], size_t sizes_length, size_t samples_count, unsigned short fill) {
  SizesWithGraphs graphs;

  for (size_t i = 0; i < sizes_length; ++i) {
    graphs[sizes[i]] = generate_filled_graphs(samples_count, sizes[i], fill);
  }

  return graphs;
}

GraphsCollection generate_map_graphs(unsigned int repeats, int size, int fill, unsigned short neighbourhood) {
  GraphsCollection graphs(repeats);

  for (unsigned int i = 0; i < repeats; ++i) {
    graph_generator* random_generator = new map_graph_generator(size, fill, neighbourhood);
    graphs[i] = std::shared_ptr<graph_generator>(random_generator);
  }

  return graphs;
}

SizesWithGraphs create_map_graphs_for_sizes(size_t sizes[], size_t sizes_length, size_t samples_count, unsigned short fill, unsigned short neighbourhood) {
  SizesWithGraphs graphs;

  for (size_t i = 0; i < sizes_length; ++i) {
    graphs[sizes[i]] = generate_map_graphs(samples_count, sizes[i], fill, neighbourhood);
  }

  return graphs;
}

