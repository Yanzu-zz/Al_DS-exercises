#ifndef SPARSEGRAPH_H
#define SPARSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"

using namespace std;

// 稀疏图 —— 使用邻接表结构实现较好
template <typename Weight>
class SparseGraph
{
private:
  int n, m;                         // 图的顶点数和边数
  bool directed;                    // 判断该图是否有向图
  vector<vector<Edge<Weight> *>> g; // 邻接表，这里不再是 bool 表示了，而是存放每个顶点与其它顶点相通的编号

public:
  SparseGraph(int n, bool directed)
  {
    this->n = n;
    this->m = m;
    this->directed = directed;

    for (int i = 0; i < n; i++)
    {
      g.push_back(vector<Edge<Weight> *>());
    }
  }

  ~SparseGraph()
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < g[i].size(); j++)
        delete g[i][j];
  }

  int V() { return n; }
  int E() { return m; }

  bool hasEdge(int v, int w)
  {
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    // 邻接表的逻辑里判断两个顶点是否有相通的边就必须写循环判断了
    for (int i = 0; i < g[v].size(); i++)
    {
      if (g[v][i]->other(v) == w)
      {
        return true;
      }

      return false;
    }
  }

  // 在顶点 v和w 之间添加一条边
  void addEdge(int v, int w, Weight weight)
  {
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    // 如果和稠密边一样在 addEdge 里判断是否有相通边，那么 addEdge 时间复杂度也会变成 O(n)
    // 所以我们先允许该图可以拥有平行边（平行边即两顶点间有多条边）
    // 去除平行边的操作一般是先把整张图的数据给读取，然后综合一起来删除掉

    g[v].push_back(new Edge<Weight>(v, w, weight));
    if (v != w && !directed)
    {
      g[w].push_back(new Edge<Weight>(v, w, weight));
    }

    m++;
  }

  // 展示顶点相连通情况
  void show()
  {
    for (int i = 0; i < n; i++)
    {
      cout << "vertex " << i << ":\t";
      for (int j = 0; j < g[i].size(); j++)
      {
        cout << "( to:" << g[i][j]->w() << ",wt:" << g[i][j]->wt() << ")\t";
      }
      cout << endl;
    }
  }

  // SparseGraph 相邻顶点的迭代器类
  // 用这种子类的方法可以避免向用户曝光 g 图中的数据（因为迭代器可以隐藏迭代的过程）
  class adjIterator
  {
  private:
    int v;     // 需要看有几条边的顶点
    int index; // 存放当前迭代到哪里了的变量
    SparseGraph &G;

  public:
    // 初始化要传入需要迭代的图的地址以及需要知道顶点v的边
    // 由于 G 是引用的方法初始化的，所以我们就用构造列表的方式把它传值
    adjIterator(SparseGraph &graph, int v) : G(graph)
    {
      this->v = v;
      this->index = 0;
    }

    // 获取顶点的第一条边
    Edge<Weight>* begin()
    {
      index = 0;
      if (G.g[v].size())
      {
        // 如果需要迭代的顶点边数不为空的话，返回第一条边（用来 next 继续迭代）
        return G.g[v][index];
      }

      return NULL;
    }

    // 获取（上一条操作的）下一条边
    Edge<Weight>* next()
    {
      index++;
      if (index < G.g[v].size())
      {
        return G.g[v][index];
      }

      return NULL;
    }

    // 判断迭代是否该结束
    bool end()
    {
      return index >= G.g[v].size();
    }
  };
};

#endif
