#include "graph_generator.h"

#include <algorithm>
#include <limits.h>

#define VERBOSE 1

graph_generator::Weight graph_generator::NO_EDGE = INT_MAX;
graph_generator::Weight graph_generator::MAX_WEIGHT = 10;

graph_generator::graph_generator() :
    m_size(7), m_original_graph(new Weight*[m_size]), m_boost_graph(
        new BoostSimpleGraph(m_size)) {
  const int n = 7;
  const unsigned int x = NO_EDGE;
  //                                    0  1  2  3  4  5  6
  m_original_graph[0] = new Weight[n] { 0, 1, x, 1, 1, x, x };
  m_original_graph[1] = new Weight[n] { 1, 0, 1, x, 1, x, x };
  m_original_graph[2] = new Weight[n] { x, 1, 0, x, x, x, 1 };
  m_original_graph[3] = new Weight[n] { 1, x, x, 0, 1, x, 1 };
  m_original_graph[4] = new Weight[n] { 1, 1, x, 1, 0, 1, x };
  m_original_graph[5] = new Weight[n] { x, x, x, x, 1, 0, x };
  m_original_graph[6] = new Weight[n] { x, x, 1, 1, x, x, 0 };

  original_to_boost();
}

graph_generator::graph_generator(size_t size, int fill) :
    m_size(size), m_original_graph(new Weight*[m_size]), m_boost_graph(
        new BoostSimpleGraph(m_size)) {
  for (size_t i = 0; i < m_size; i++) {
    m_original_graph[i] = new Weight[m_size];
    m_original_graph[i][i] = 0;
    for (size_t j = 0; j < i; j++) {
      bool is_connected = (rand() % 100) < fill;
      m_original_graph[i][j] = m_original_graph[j][i] = is_connected ? (rand() % MAX_WEIGHT) : NO_EDGE;
    }
  }

  enhance_graph_connectivity();
  original_to_boost();
}

void graph_generator::enhance_graph_connectivity() {
  for (size_t i = 0; i < m_size; i++) {
    int edges_count = std::count(m_original_graph[i],
        m_original_graph[i] + m_size, 1);
    if (edges_count == 1) {
      int edge_number = generate_edge_number(i);
      m_original_graph[i][edge_number] = m_original_graph[edge_number][i] = MAX_WEIGHT;
    }
  }
}

size_t graph_generator::generate_edge_number(size_t i) {
  size_t edge_number = (rand() % (m_size - 1));
  if (edge_number >= i) {
    edge_number += 1;
  }
  return edge_number;
}

void graph_generator::original_to_boost() {
  typename boost::graph_traits<BoostWeightedGraph>::vertex_descriptor u, v;
  typename boost::graph_traits<BoostWeightedDirectedGraph>::vertex_descriptor u2, v2;

  for (size_t i = 0; i < m_size; i++) {
    for (size_t j = 0; j < i; j++) {
      if (m_original_graph[i][j] != NO_EDGE) {
        boost::add_edge(i, j, *m_boost_graph);

        u = boost::vertex(i, m_boost_weighted_graph);
        v = boost::vertex(j, m_boost_weighted_graph);
        boost::add_edge(u, v, m_original_graph[i][j], m_boost_weighted_graph);

        u2 = boost::vertex(i, m_boost_weighted_directed_graph);
		v2 = boost::vertex(j, m_boost_weighted_directed_graph);
		boost::add_edge(u2, v2, m_original_graph[i][j], m_boost_weighted_directed_graph);
      }
    }
  }
}

graph_generator::~graph_generator() {
  for (size_t i = 0; i < m_size; i++) {
    delete[] m_original_graph[i];
  }
  delete[] m_original_graph;
}

void graph_generator::print() {
  for (size_t i = 0; i < m_size; i++) {
    for (size_t j = 0; j < m_size; j++) {
      std::cout << m_original_graph[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

graph_generator::OriginalGraph graph_generator::original_graph() {
  return m_original_graph;
}

std::shared_ptr<graph_generator::BoostSimpleGraph> graph_generator::boost_graph() {
  return m_boost_graph;
}

const size_t graph_generator::size() {
  return m_size;
}

graph_generator::BoostSimpleGraph::vertex_descriptor graph_generator::boost_initial_vertex() {
  return boost::vertex(0, *m_boost_graph);
}

graph_generator::BoostWeightedGraph graph_generator::boost_weighted_graph() {
  return m_boost_weighted_graph;
}

graph_generator::BoostWeightedDirectedGraph graph_generator::boost_weighted_directed_graph() {
  return m_boost_weighted_directed_graph;
}
