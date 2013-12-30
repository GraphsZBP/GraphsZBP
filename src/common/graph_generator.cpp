#include "graph_generator.h"

#include <algorithm>
#include <limits.h>

graph_generator::AdjacencyMatrixElement graph_generator::NO_EDGE = INT_MAX;

graph_generator::graph_generator() :
    m_size(7), m_original_graph(new AdjacencyMatrixElement*[m_size]), m_boost_graph(
        new BoostSimpleGraph(m_size)) {
  boost::add_edge(0, 1, *m_boost_graph);
  boost::add_edge(0, 3, *m_boost_graph);
  boost::add_edge(0, 4, *m_boost_graph);
  boost::add_edge(1, 2, *m_boost_graph);
  boost::add_edge(1, 4, *m_boost_graph);
  boost::add_edge(2, 6, *m_boost_graph);
  boost::add_edge(3, 4, *m_boost_graph);
  boost::add_edge(3, 6, *m_boost_graph);
  boost::add_edge(4, 5, *m_boost_graph);

  const int n = 7;
  const unsigned int x = NO_EDGE;
  //                                                    0  1  2  3  4  5  6
  m_original_graph[0] = new AdjacencyMatrixElement[n] { 1, 1, x, 1, 1, x, x };
  m_original_graph[1] = new AdjacencyMatrixElement[n] { 1, 1, 1, x, 1, x, x };
  m_original_graph[2] = new AdjacencyMatrixElement[n] { x, 1, 1, x, x, x, 1 };
  m_original_graph[3] = new AdjacencyMatrixElement[n] { 1, x, x, 1, 1, x, 1 };
  m_original_graph[4] = new AdjacencyMatrixElement[n] { 1, 1, x, 1, 1, 1, x };
  m_original_graph[5] = new AdjacencyMatrixElement[n] { x, x, x, x, 1, 1, x };
  m_original_graph[6] = new AdjacencyMatrixElement[n] { x, x, 1, 1, x, x, 1 };
}

graph_generator::graph_generator(int size, int fill) :
    m_size(size), m_original_graph(new AdjacencyMatrixElement*[m_size]), m_boost_graph(
        new BoostSimpleGraph(m_size)) {
  for (int i = 0; i < m_size; i++) {
    m_original_graph[i] = new AdjacencyMatrixElement[m_size];
    m_original_graph[i][i] = 1;
    for (int j = 0; j < i; j++) {
      bool is_connected = (rand() % 100) < fill;
      m_original_graph[i][j] = m_original_graph[j][i] = is_connected;
      if (is_connected) {
        boost::add_edge(i, j, *m_boost_graph);
      }
    }
  }

  enhance_graph_connectivity();
}

void graph_generator::enhance_graph_connectivity() {
  for (int i = 0; i < m_size; i++) {
    int edges_count = std::count(m_original_graph[i],
        m_original_graph[i] + m_size, 1);
    if (edges_count == 1) {
      int edge_number = generate_edge_number(i);
      m_original_graph[i][edge_number] = m_original_graph[edge_number][i] = 1;
      boost::add_edge(i, edge_number, *m_boost_graph);
    }
  }
}

int graph_generator::generate_edge_number(int i) {
  int edge_number = (rand() % (m_size - 1));
  if (edge_number >= i) {
    edge_number += 1;
  }
  return edge_number;
}

graph_generator::~graph_generator() {
  const int n = 7;
  for (int i = 0; i < n; i++) {
    delete[] m_original_graph[i];
  }
  delete[] m_original_graph;
}

void graph_generator::print() {
  for (int i = 0; i < m_size; i++) {
    for (int j = 0; j < m_size; j++) {
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
