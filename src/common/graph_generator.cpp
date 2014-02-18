#include "graph_generator.h"

#include <algorithm>

#define VERBOSE 1

zbp::weight graph_generator::MIN_WEIGHT = 1;
zbp::weight graph_generator::MAX_WEIGHT = 9;

graph_generator::graph_generator() :
    m_size(7), m_fill(100), m_original_graph(new zbp::weight*[m_size]), m_boost_graph(new BoostSimpleGraph(m_size)) {
  const int n = 7;
  const zbp::weight x = zbp::NO_EDGE;
  //										   0  1  2  3  4  5  6
  m_original_graph[0] = new zbp::weight[n] { 0, 1, x, 1, 1, x, x };
  m_original_graph[1] = new zbp::weight[n] { 1, 0, 1, x, 1, x, x };
  m_original_graph[2] = new zbp::weight[n] { x, 1, 0, x, x, x, 1 };
  m_original_graph[3] = new zbp::weight[n] { 1, x, x, 0, 1, x, 1 };
  m_original_graph[4] = new zbp::weight[n] { 1, 1, x, 1, 0, 1, x };
  m_original_graph[5] = new zbp::weight[n] { x, x, x, x, 1, 0, x };
  m_original_graph[6] = new zbp::weight[n] { x, x, 1, 1, x, x, 0 };
}

graph_generator::graph_generator(size_t size, int fill) :
    m_size(size), m_fill(fill) {
}

size_t graph_generator::generate_edge_number(size_t i) {
  size_t edge_number = (rand() % (m_size - 1));
  if (edge_number >= i) {
    edge_number += 1;
  }
  return edge_number;
}

graph_generator::~graph_generator() {
  free_all_memory();
}

void graph_generator::print() {
  for (size_t i = 0; i < m_size; i++) {
    for (size_t j = 0; j < m_size; j++) {
      if (m_original_graph[i][j] == zbp::NO_EDGE) {
        std::cout << 'x' << " ";
      } else {
        std::cout << m_original_graph[i][j] << " ";
      }
    }
    std::cout << std::endl;
  }
}

zbp::distance_matrix graph_generator::original_graph() {
  if (m_original_graph == NULL) {
    m_original_graph = new zbp::weight*[m_size];
    for (size_t i = 0; i < m_size; i++) {
      m_original_graph[i] = new zbp::weight[m_size];
      std::fill(m_original_graph[i], m_original_graph[i] + m_size, zbp::NO_EDGE);
    }

    for (size_t i = 0; i < m_size; i++) {
      m_original_graph[i][i] = 0;
      for (size_t j = 0; j < i; j++) {
        m_original_graph[i][j] = m_original_graph[j][i] = random_edge();
      }
    }
  }
  return m_original_graph;
}

zbp::weight graph_generator::random_edge() {
  bool is_connected = (rand() % 100) < m_fill;
  return is_connected ? (MIN_WEIGHT + (rand() % MAX_WEIGHT)) : zbp::NO_EDGE;
}

std::shared_ptr<graph_generator::BoostSimpleGraph> graph_generator::boost_graph() {
  if (!m_boost_graph) {
    graph_generator::BoostSimpleGraph* p = new BoostSimpleGraph(m_size);
    m_boost_graph = std::shared_ptr<graph_generator::BoostSimpleGraph>(p);

    for (size_t i = 0; i < m_size; i++) {
      for (size_t j = 0; j < i; j++) {
        if (m_original_graph[i][j] != zbp::NO_EDGE) {
          boost::add_edge(i, j, *m_boost_graph);
        }
      }
    }
  }

  return m_boost_graph;
}

std::shared_ptr<graph_generator::BoostWeightedGraph> graph_generator::boost_weighted_graph() {
  if (!m_boost_weighted_graph) {
    graph_generator::BoostWeightedGraph* p = new BoostWeightedGraph();
    m_boost_weighted_graph = std::shared_ptr<BoostWeightedGraph>(p);
    boost::graph_traits<BoostWeightedGraph>::vertex_descriptor u, v;

    for (size_t i = 0; i < m_size; i++) {
      for (size_t j = 0; j < i; j++) {
        if (m_original_graph[i][j] != zbp::NO_EDGE) {
          u = boost::vertex(i, *m_boost_weighted_graph);
          v = boost::vertex(j, *m_boost_weighted_graph);
          boost::add_edge(u, v, m_original_graph[i][j], *m_boost_weighted_graph);
        }
      }
    }
  }

  return m_boost_weighted_graph;
}

std::shared_ptr<graph_generator::BoostJohnsonGraph> graph_generator::boost_johnson_graph() {
  if (!m_boost_johnson_graph) {
    graph_generator::BoostJohnsonGraph* p = new BoostJohnsonGraph();
    m_boost_johnson_graph = std::shared_ptr<BoostJohnsonGraph>(p);
    boost::graph_traits<BoostJohnsonGraph>::vertex_descriptor u, v;

    for (size_t i = 0; i < m_size; i++) {
      for (size_t j = 0; j < i; j++) {
        if (m_original_graph[i][j] != zbp::NO_EDGE) {
          u = boost::vertex(i, *m_boost_johnson_graph);
          v = boost::vertex(j, *m_boost_johnson_graph);
          boost::add_edge(u, v, m_original_graph[i][j], *m_boost_johnson_graph);
        }
      }
    }
  }

  return m_boost_johnson_graph;
}

const size_t graph_generator::size() {
  return m_size;
}

graph_generator::BoostSimpleGraph::vertex_descriptor graph_generator::boost_initial_vertex() {
  return boost::vertex(0, *m_boost_graph);
}

void graph_generator::free_all_memory() {
  if (m_original_graph != NULL) {
    for (size_t i = 0; i < m_size; i++) {
      delete[] m_original_graph[i];
    }
    delete[] m_original_graph;
    m_original_graph = NULL;
  }
  free_boost_memory();
}

void graph_generator::free_boost_memory() {
  m_boost_graph.reset();
  m_boost_weighted_graph.reset();
  m_boost_johnson_graph.reset();
}
