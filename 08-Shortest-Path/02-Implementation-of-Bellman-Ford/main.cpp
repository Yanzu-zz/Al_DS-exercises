#include <iostream>
#include "../Graph.h"
#include "BellmanFord.h"

using namespace std;

int main()
{
  string filename = "../testG2.txt";
  // string filename = "../testG_negative_circle.txt";
  int V = 5;

  // 在无向图中，只要有一条边为负权边，那么该图就会形成一个负权环
  SparseGraph<int> g = SparseGraph<int>(V, true);
  ReadGraph<SparseGraph<int>, int> readGraph(g, filename);

  cout << "Test Bellman-Ford:" << endl
       << endl;
  BellmanFord<SparseGraph<int>, int> bellmanFord(g, 0);
  if (bellmanFord.negativeCycle())
    cout << "The graph contain negative cycle!" << endl;
  else
    for (int i = 1; i < V; i++)
    {
      cout << "Shortest Path to " << i << " : " << bellmanFord.shortestPathTo(i) << endl;
      bellmanFord.showPath(i);
      cout << "----------" << endl;
    }

  return 0;
}
