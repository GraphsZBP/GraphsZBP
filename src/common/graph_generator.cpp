#include "graph_generator.h"

#include <algorithm>

graph_generator::graph_generator() :
    m_size(7), m_original_graph(new int*[m_size]), m_boost_graph(
        boost::adjacency_matrix<boost::undirectedS>(m_size)) {
  boost::add_edge(0, 1, m_boost_graph);
  boost::add_edge(0, 3, m_boost_graph);
  boost::add_edge(0, 4, m_boost_graph);
  boost::add_edge(1, 2, m_boost_graph);
  boost::add_edge(1, 4, m_boost_graph);
  boost::add_edge(2, 6, m_boost_graph);
  boost::add_edge(3, 4, m_boost_graph);
  boost::add_edge(3, 6, m_boost_graph);
  boost::add_edge(4, 5, m_boost_graph);

  const int n = 7;
  //                                 0  1  2  3  4  5  6
  m_original_graph[0] = new int[n] { 1, 1, 0, 1, 1, 0, 0 };
  m_original_graph[1] = new int[n] { 1, 1, 1, 0, 1, 0, 0 };
  m_original_graph[2] = new int[n] { 0, 1, 1, 0, 0, 0, 1 };
  m_original_graph[3] = new int[n] { 1, 0, 0, 1, 1, 0, 1 };
  m_original_graph[4] = new int[n] { 1, 1, 0, 1, 1, 1, 0 };
  m_original_graph[5] = new int[n] { 0, 0, 0, 0, 1, 1, 0 };
  m_original_graph[6] = new int[n] { 0, 0, 1, 1, 0, 0, 1 };
}

graph_generator::graph_generator(int size, int fill) :
    m_size(size), m_original_graph(new int*[m_size]), m_boost_graph(
        boost::adjacency_matrix<boost::undirectedS>(m_size)) {
  for (int i = 0; i < m_size; i++) {
    m_original_graph[i] = new int[m_size];
    m_original_graph[i][i] = 1;
    for (int j = 0; j < i; j++) {
      bool is_connected = (rand() % 100) < fill;
      m_original_graph[i][j] = m_original_graph[j][i] = is_connected;
      if (is_connected) {
        boost::add_edge(i, j, m_boost_graph);
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
      boost::add_edge(i, edge_number, m_boost_graph);
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

int** graph_generator::original_graph() {
  return m_original_graph;
}

boost::adjacency_matrix<boost::undirectedS> graph_generator::boost_graph() {
  return m_boost_graph;
}

size_t graph_generator::size() {
  return m_size;
}

boost::adjacency_matrix<boost::undirectedS>::vertex_descriptor graph_generator::boost_initial_vertex() {
  return boost::vertex(0, m_boost_graph);
}
