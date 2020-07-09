#include <iostream>
#include <vector>
#include <stack>
#include "../Edge.h"
#include "../IndexMinHeap.h"

using namespace std;

template <typename Graph, typename Weight>
class Dijkstra
{
private:
  Graph &G;
  int s;
  Weight *distTo;              // 点 a 到其它点的最短距离数组（通过松弛操作变最短）
  bool *marked;                // 记录一个节点是否以其为松弛点松弛过
  vector<Edge<Weight> *> from; // 记录到达的节点是从哪条边来的

public:
  Dijkstra(Graph &graph, int s) : G(graph)
  {
    this->s = s;
    distTo = new Weight[G.V()];
    marked = new bool[G.V()];

    for (int i = 0; i < G.V(); i++)
    {
      distTo[i] = Weight();
      marked[i] = false;
      from.push_back(NULL);
    }

    IndexMinHeap<Weight> ipq(G.V());

    // Dijkstra
    distTo[s] = Weight();
    marked[s] = true;
    ipq.insert(s, distTo[s]);

    while (!ipq.isEmpty())
    {
      int v = ipq.extractMinIndex();

      // distTo[v] 就是 s 到 v 的最短路径
      marked[v] = true;

      // Relaxation 松弛操作
      typename Graph::adjIterator adj(G, v);
      for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
      {
        int w = e->other(v);
        if (!marked[w])
        {
          // 判断从 v 到 w是否没走过或者比其他结点更短
          if (from[w] == NULL || distTo[v] + e->wt() < distTo[w])
          {
            // 是的话就进行松弛操作
            distTo[w] = distTo[v] + e->wt();
            from[w] = e;

            // 更新最短路径
            if (ipq.contain(w))
            {
              ipq.change(w, distTo[w]);
            }
            else
            {
              ipq.insert(w, distTo[w]);
            }
          }
        }
      } // Relaxation 松弛操作结束
    }
  }

  ~Dijkstra()
  {
    delete[] distTo, marked;
  }

  Weight shortestPathTo(int w)
  {
    assert(w >= 0 && w < G.V());
    return distTo[w];
  }

  bool hasPathTo(int w)
  {
    assert(w >= 0 && w < G.V());
    return marked[w];
  }

  void shortestPath(int w, vector<Edge<Weight>> &vec)
  {

    assert(w >= 0 && w < G.V());

    stack<Edge<Weight> *> s;
    Edge<Weight> *e = from[w];
    while (e->v() != this->s)
    {
      s.push(e);
      e = from[e->v()];
    }
    s.push(e);

    while (!s.empty())
    {
      e = s.top();
      vec.push_back(*e);
      s.pop();
    }
  }

  void showPath(int w)
  {

    assert(w >= 0 && w < G.V());

    vector<Edge<Weight>> vec;
    shortestPath(w, vec);
    for (int i = 0; i < vec.size(); i++)
    {
      cout << vec[i].v() << " -> ";
      if (i == vec.size() - 1)
        cout << vec[i].w() << endl;
    }
  }
};
