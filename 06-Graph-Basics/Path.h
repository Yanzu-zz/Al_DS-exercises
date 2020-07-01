#ifndef INC_06_FINDING_A_PATH_PATH_H
#define INC_06_FINDING_A_PATH_PATH_H

#include <vector>
#include <stack>
#include <iostream>
#include <cassert>

using namespace std;

template <typename Graph>
class Path
{

private:
  // 其它变量用处和 Component.h 中一致
  Graph &G;
  int s;
  bool *visited;
  int *from; // 记录当前访问的节点是从哪个节点过来的

  // 图的深度优先遍历算法函数
  void dfs(int v)
  {
    visited[v] = true;

    // 这里就可以复用之前我们写过的图的迭代算法，怎么样，察觉到模块化代码的魅力了吗？
    // 为了告诉编译器 adjIterator 是 Graph 中的一个类型而不是成员变量，我们要在前面加上 typename 关键字
    typename Graph::adjIterator adj(G, v);

    // 这里就是典型的迭代（型循环）的写法，不多解释
    for (int i = adj.begin(); !adj.end(); i = adj.next())
    {
      if (!visited[i])
      {
        from[i] = v; // 表明我们访问的 i 节点是从 v 节点过来的
        dfs(i);
      }
    }
  }

public:
  // 对图 graph 而言，求节点 s 到其它任意点的路径
  Path(Graph &graph, int s) : G(graph)
  {

    // 算法初始化
    assert(s >= 0 && s < G.V());

    visited = new bool[G.V()];
    from = new int[G.V()];
    for (int i = 0; i < G.V(); i++)
    {
      visited[i] = false;
      from[i] = -1;
    }
    this->s = s;

    // 寻路算法
    dfs(s);
  }

  ~Path()
  {

    delete[] visited, from;
  }

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
};

#endif //INC_06_FINDING_A_PATH_PATH_H
