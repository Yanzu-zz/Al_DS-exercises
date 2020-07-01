#include <iostream>
#include "../Graph.h"

using namespace std;

int main(void)
{
  string filename = "../testG2.txt";
  SparseGraph g = SparseGraph(7, false);
  ReadGraph<SparseGraph> readGraph(g, filename);
  g.show();
  cout << endl;

  Path<SparseGraph> dfs(g, 0);
  cout << "DFS : ";
  dfs.showPath(6);

  return 0;
}
