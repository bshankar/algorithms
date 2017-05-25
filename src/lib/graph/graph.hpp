#ifndef GRAPH_H
#define GRAPH_H

#include "union_find.hpp"
#include <vector>
using std::vector;


template <class T, class W>
class Graph {
public:
  Graph(int size, bool digraph = false, bool edgeWeights = false)
    : digraph(digraph), edgeWeights(edgeWeights) {
    adjList.resize(size, vector<T>(0));
    if (edgeWeights)
      edgeWts.resize(size, vector<T>(0));
  }


  void addEdge(T v1, T v2) {
    adjList[v1].push_back(v2);

    if (!digraph)
      adjList[v2].push_back(v1);
  }


  bool addEdge(T v1, T v2, W wt) {
    // add a weighted edge between v1 and v2
    addEdge(v1, v2);
    edgeWts[v1].push_back(wt);

    if (!digraph)
      edgeWts[v2].push_back(wt);
  }


  // graph traversal
  void dfs();
  void bfs();
  void isConnected();

  // MST
  void kruskal();

  // SCC
  void tarjan();

  // shortest paths
  void bellmanFord();
  void dikstra();
  void floydWarshall();

  // NP-hard
  void tsp();
  void color();

  // Paths and circuits

  // flows and cuts

private:
  vector<vector<T> > adjList;
  vector<vector<W> > edgeWts;
  bool digraph, edgeWeights;
};

#endif
