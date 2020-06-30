#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 稠密图 —— 使用邻接矩阵结构实现比较好
class DenseGraph
{
private:
  int n, m;               // n 为图的顶点数，m 为边数
  bool directed;          // 判断为 有向/无向图
  vector<vector<bool>> g; // 用 vector 类型来表示邻接矩阵（好）

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
      g.push_back(vector<bool>(n, false));
    }
  }

  ~DenseGraph() {}

  // 返回当前图有多少个顶点或边
  int V() { return n; }
  int E() { return m; }

  // 查看顶点 v和w 之间是否存在一条边
  bool hasEdge(int v, int w)
  {
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    return g[v][w];
  }

  // 为图在顶点 v和w 之间添加一条边（即连通它们）
  void addEdge(int v, int w)
  {
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    // 如果两顶点之间已经存在边了，不用进行操作，返回即可
    // 目的是防止总边数 m 再次 +1
    // 但是这样操作就把图可能存在的平行边给去了（平行边级两顶点之间有多条边且值可能不同）
    if (hasEdge(v, w))
    {
      return;
    }

    g[v][w] = true;
    if (!directed)
    {
      g[w][v] = true;
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
        cout << g[i][j] << "\t";
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
    int begin()
    {
      index = -1;
      return next();
    }

    // 获取（上一条操作的）下一条边
    int next()
    {
      for (index += 1; index < G.V(); index++)
      {
        if (G.g[v][index])
        {
          return index;
        }
      }

      return -1;
    }

    // 判断循环是否该结束
    bool end()
    {
      return index >= G.V();
    }
  };
};
