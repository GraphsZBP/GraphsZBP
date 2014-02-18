#include "map_graph_generator.h"

#include <algorithm>

map_graph_generator::~map_graph_generator() {
}

map_graph_generator::map_graph_generator(size_t size, int fill, unsigned int neighbourhood_size) :
    graph_generator(size, fill), m_neighbourhood_size(neighbourhood_size) {
}

zbp::distance_matrix map_graph_generator::original_graph() {
  if (m_original_graph == NULL) {
    m_original_graph = new zbp::weight*[m_size];
    for (size_t i = 0; i < m_size; i++) {
      m_original_graph[i] = new zbp::weight[m_size];
      std::fill(m_original_graph[i], m_original_graph[i] + m_size, zbp::NO_EDGE);
    }

    for (size_t i = 0; i < m_size; i++) {
      size_t left = i > m_neighbourhood_size ? i - m_neighbourhood_size : 0;
      size_t right = i + m_neighbourhood_size < m_size ? i + m_neighbourhood_size : m_size - 1;

      for (size_t j = left; j <= right; ++j) {
        if (i == j) {
          m_original_graph[i][i] = 0;
        } else {
          m_original_graph[i][j] = m_original_graph[j][i] = random_edge();
        }
      }
    }
  }
  return m_original_graph;
}
