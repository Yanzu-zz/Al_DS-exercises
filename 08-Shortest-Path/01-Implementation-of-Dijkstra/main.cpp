// dijkstra 单源最短路径算法（一个点到其它节点的最短路径）
#include <iostream>
#include "../Graph.h"
#include "Dijkstra.h"

using namespace std;

int main()
{

  string filename = "../testG1.txt";
  int V = 5;

  SparseGraph<int> g = SparseGraph<int>(V, true);
  //SparseGraph<int> g = SparseGraph<int>(V, false);
  ReadGraph<SparseGraph<int>, int> readGraph(g, filename);

  cout << "Test Dijkstra:" << endl << endl;
  Dijkstra<SparseGraph<int>, int> dij(g, 0);
  for (int i = 1; i < V; i++)
  {
    cout << "Shortest Path to " << i << " : " << dij.shortestPathTo(i) << endl;
    dij.showPath(i);
    cout << "----------" << endl;
  }

  return 0;
}
