#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"

using namespace std;

// 稠密图 —— 使用邻接矩阵结构实现比较好
template <typename Weight>
class DenseGraph
{
private:
  int n, m;      // n 为图的顶点数，m 为边数
  bool directed; // 判断为 有向/无向图
  // 不再是简单的bool类型的vector了，而是 Edge<Weight> 类型的指针
  // 用指针是为了方便表达 “空” 这个概念
  vector<vector<Edge<Weight> *>> g;

public:
  DenseGraph(int n, bool directed)
  {
    this->n = n;
    this->m = 0;
    this->directed = directed;

    // 初始化 n*n 的邻接矩阵
    for (int i = 0; i < n; i++)
    {
      // 不需要两个循环，写法高级点就vans了
      g.push_back(vector<Edge<Weight> *>(n, NULL));
    }
  }

  ~DenseGraph()
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (g[i][j] != NULL)
          delete g[i][j];
  }

  // 返回当前图有多少个顶点或边
  int V() { return n; }
  int E() { return m; }

  // 查看顶点 v和w 之间是否存在一条边
  bool hasEdge(int v, int w)
  {
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    return g[v][w] != NULL;
  }

  // 为图在顶点 v和w 之间添加一条带权边
  void addEdge(int v, int w, Weight weight)
  {
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    // 这里和之前的无权图不同，如判断之前有边存在，不能直接返回
    // 要先把之前的数据删除，再赋值新的数据
    if (hasEdge(v, w))
    {
      delete g[v][w];

      // 无向图要双向删除
      if (!directed)
      {
        delete g[w][v];
      }

      m--;
    }

    g[v][w] = new Edge<Weight>(v, w, weight);
    if (!directed)
    {
      g[w][v] = new Edge<Weight>(v, w, weight);
    }

    m++; // 维护总边数量
  }

  // 展示顶点相连通情况
  void show()
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (g[i][j])
        {
          cout << g[i][j]->wt() << "\t";
        }
        else
        {
          cout << "NULL\t";
        }
      }
      cout << endl;
    }
  }

  // 稠密图的邻边迭代器（循环）
  class adjIterator
  {
  private:
    int v;     // 需要看有几条边的顶点
    int index; // 存放当前循环到哪里了的变量
    DenseGraph &G;

  public:
    // 初始化要传入需要循环查看的图的地址以及需要知道顶点v的边
    // 由于 G 是引用的方法初始化的，所以我们就用构造列表的方式把它传值
    adjIterator(DenseGraph &graph, int v) : G(graph)
    {
      this->v = v;
      this->index = -1;
    }

    // 获取顶点的第一条边
    Edge<Weight> *begin()
    {
      index = -1;
      return next();
    }

    // 获取（上一条操作的）下一条边
    Edge<Weight> *next()
    {
      for (index += 1; index < G.V(); index++)
      {
        if (G.g[v][index])
        {
          return G.g[v][index];
        }
      }

      return NULL;
    }

    // 判断循环是否该结束
    bool end()
    {
      return index >= G.g[v].size();
    }
  };
};
