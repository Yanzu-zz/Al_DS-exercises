#include <iostream>
#include <cstring>
#include "../Graph.h"

using namespace std;

int main(void)
{
  // TestG1.txt
  string filename1 = "../testG1.txt";
  SparseGraph g1 = SparseGraph(13, false);
  ReadGraph<SparseGraph> readGraph1(g1, filename1);
  Component<SparseGraph> component1(g1);
  // 查看 g1 的连通分量数量
  cout << "TestG1.txt, Component Count: " << component1.count() << endl;

  cout << endl;

  // TestG2.txt
  string filename2 = "../testG2.txt";
  SparseGraph g2 = SparseGraph(7, false);
  ReadGraph<SparseGraph> readGraph2(g2, filename2);
  Component<SparseGraph> component2(g2);
  // g2 连通分量数量
  cout << "TestG2.txt, Component Count: " << component2.count() << endl;

  return 0;
}
