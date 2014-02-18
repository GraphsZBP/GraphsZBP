#include "map_graph_generator.h"


map_graph_generator::map_graph_generator()
{
}


map_graph_generator::~map_graph_generator()
{
}
map_graph_generator::map_graph_generator(size_t size, int fill) : graph_generator(size,fill) 
{
}

zbp::distance_matrix map_graph_generator::original_graph() {
	if (m_original_graph == NULL) {
		m_original_graph = new zbp::weight*[m_size];
		for (size_t i = 0; i < m_size; i++) {
			m_original_graph[i] = new zbp::weight[m_size]{zbp::NO_EDGE};
			m_original_graph[i][i] = 0;
			bool is_connected;
			for (int j = i - 2; (j <= i + 2) && (j < m_size); ++j) {
				if (j > 0 && j != i) {
					is_connected = (rand() % 100) < m_fill;
					m_original_graph[i][j] = is_connected ? (rand() % MAX_WEIGHT) : zbp::NO_EDGE;
				}
			}
		}
	}
	return m_original_graph;
}