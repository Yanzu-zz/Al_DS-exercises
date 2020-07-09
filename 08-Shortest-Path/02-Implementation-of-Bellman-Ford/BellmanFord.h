#ifndef INC_05_IMPLEMENTATION_OF_BELLMAN_FORD_BELLMANFORD_H
#define INC_05_IMPLEMENTATION_OF_BELLMAN_FORD_BELLMANFORD_H

#include <stack>
#include <vector>
#include "../Edge.h"

using namespace std;

template <typename Graph, typename Weight>
class BellmanFord
{

private:
  Graph &G;
  int s;
  Weight *distTo;
  vector<Edge<Weight> *> from;
  bool hasNegativeCycle; // 判断传进来的图是否有负权环

  // 就是在对所有的顶点做一轮循环操作
  // 如果还能继续松弛或者有顶点还未被访问过，那这个图就存在负权环
  bool detectNegativeCycle()
  {
    for (int i = 0; i < G.V(); i++)
    {
      typename Graph::adjIterator adj(G, i);
      for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
        if (!from[e->w()] || distTo[e->v()] + e->wt() < distTo[e->w()])
          return true;
    }

    return false;
  }

public:
  BellmanFord(Graph &graph, int s) : G(graph)
  {

    this->s = s;
    distTo = new Weight[G.V()];
    for (int i = 0; i < G.V(); i++)
    {
      from.push_back(NULL);
    }

    // Bellman-Ford
    distTo[s] = Weight();

    // 对图中的所有的点进行 v-1 次的松弛（因为有负权边，当前节点最短边不一定就是最短路径）
    for (int pass = 1; pass < G.V(); pass++)
    {
      // Relaxation
      for (int i = 0; i < G.V(); i++)
      {
        typename Graph::adjIterator adj(G, i);
        for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
        {
          if (!from[e->w()] || distTo[e->v()] + e->wt() < distTo[e->w()])
          {
            distTo[e->w()] = distTo[e->v()] + e->wt();
            from[e->w()] = e;
          }
        }
      }
    }

    hasNegativeCycle = detectNegativeCycle();
  }

  ~BellmanFord()
  {

    delete[] distTo;
  }

  bool negativeCycle()
  {
    return hasNegativeCycle;
  }

  Weight shortestPathTo(int w)
  {
    assert(w >= 0 && w < G.V());
    assert(!hasNegativeCycle);
    return distTo[w];
  }

  bool hasPathTo(int w)
  {
    assert(w >= 0 && w < G.V());
    return from[w] != NULL;
  }

  void shortestPath(int w, vector<Edge<Weight>> &vec)
  {

    assert(w >= 0 && w < G.V());
    assert(!hasNegativeCycle);

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
    assert(!hasNegativeCycle);

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

#endif //INC_05_IMPLEMENTATION_OF_BELLMAN_FORD_BELLMANFORD_H
