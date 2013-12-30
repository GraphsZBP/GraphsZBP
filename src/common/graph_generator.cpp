#include "graph_generator.h"

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
        m_size(7), m_original_graph(new int*[m_size]), m_boost_graph(
            boost::adjacency_matrix<boost::undirectedS>(m_size)) {
}

graph_generator::~graph_generator() {
  const int n = 7;
  for (int i = 0; i < n; i++) {
    delete[] m_original_graph[i];
  }
  delete[] m_original_graph;
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
