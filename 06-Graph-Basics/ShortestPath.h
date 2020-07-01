#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <cassert>

using namespace std;

template <typename Graph>
class ShortestPath
{

private:
  // 其它变量用处和 Component.h 中一致
  Graph &G;
  int s;
  bool *visited;
  int *from; // 记录当前访问的节点是从哪个节点过来的
  int *ord;  // 记录从节点 s 到每一个节点的最短距离是多少

public:
  // 对图 graph 而言，求节点 s 到其它任意点的路径
  ShortestPath(Graph &graph, int s) : G(graph)
  {

    // 算法初始化
    assert(s >= 0 && s < graph.V());

    visited = new bool[graph.V()];
    from = new int[graph.V()];
    ord = new int[graph.V()];
    for (int i = 0; i < graph.V(); i++)
    {
      visited[i] = false;
      from[i] = -1;
      ord[i] = -1;
    }
    this->s = s;

    // 求无向图最短路径辅助数组
    queue<int> q;

    // 无向图最短路径算法
    // 广度优先遍历求无权图的最短路径（有向无向皆可）
    q.push(s);
    visited[s] = true;
    ord[s] = 0;
    while (!q.empty())
    {
      int v = q.front();
      q.pop();

      typename Graph::adjIterator adj(G, v);
      for (int i = adj.begin(); !adj.end(); i = adj.next())
      {
        if (!visited[i])
        {
          q.push(i);
          visited[i] = true;
          from[i] = v;
          ord[i] = ord[v] + 1; // 此节点的距离等于从它过来的这个节点的距离 +1
        }
      }
    }
  }

  ~ShortestPath()
  {

    delete[] visited, from, ord;
  }

  // 下面这三个功能函数和之前寻求路径是基本一致的，因为结构都一样

  // 判断 s 通往节点 w 是否有路
  bool hasPath(int w)
  {
    assert(w >= 0 && w < G.V());

    return visited[w];
  }

  // 判断节点 w 详细的路径，并将结果存进 vec 中
  void path(int w, vector<int> &vec)
  {
    assert(w >= 0 && w < G.V());

    stack<int> s;

    // 从 w 节点往回推
    int p = w;
    while (p != -1)
    {
      s.push(p);
      p = from[p];
    }

    vec.clear();
    while (!s.empty())
    {
      vec.push_back(s.top());
      s.pop();
    }
  }

  // 打印输出从 s 到 w 的路径
  void showPath(int w)
  {
    assert(w >= 0 && w < G.V());

    vector<int> vec;
    path(w, vec);
    for (int i = 0; i < vec.size(); i++)
    {
      cout << vec[i];
      if (i == vec.size() - 1)
      {
        cout << endl;
      }
      else
      {
        cout << " -> ";
      }
    }
  }

  int length(int w)
  {
    assert(w >= 0 && w < G.V());

    return ord[w];
  }
};
