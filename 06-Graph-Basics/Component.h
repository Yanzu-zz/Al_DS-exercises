// 以求连通分量来举图的遍历例子
#include <iostream>
#include <cassert>

using namespace std;

template <typename Graph>
class Component
{
private:
  Graph &G;
  bool *visited; // 记录某个节点是否遍历过了
  int ccount;    // 记录有多少个连通分量的数量变量
  int *id;       // 并查集思路，根据连通分量查看两个节点是否相连的数组（即相连取同id，不相连则不同）

  // 图的深度优先遍历算法函数
  void dfs(int v)
  {
    visited[v] = true;
    // 是的，只用加这一句话就完成了方法
    id[v] = ccount;

    // 这里就可以复用之前我们写过的图的迭代算法，怎么样，察觉到模块化代码的魅力了吗？
    // 为了告诉编译器 adjIterator 是 Graph 中的一个类型而不是成员变量，我们要在前面加上 typename 关键字
    typename Graph::adjIterator adj(G, v);

    // 这里就是典型的迭代（型循环）的写法，不多解释
    for (int i = adj.begin(); !adj.end(); i = adj.next())
    {
      if (!visited[i])
      {
        dfs(i);
      }
    }
  }

public:
  Component(Graph &graph) : G(graph)
  {
    // 图有多少个结点就开辟多少个 visited 空间
    visited = new bool[G.V()];
    // 虽然最终的连通数量可能很少，但这里依然要开 V() 个，并查集思路
    id = new int[G.V()];
    ccount = 0;

    for (int i = 0; i < G.V(); i++)
    {
      // 初始时每个节点都还未被访问过
      visited[i] = false;
      id[i] = -1;
    }

    for (int i = 0; i < G.V(); i++)
    {
      // 判断当前节点是否被访问过，若无，从该点处进行深度遍历
      if (!visited[i])
      {
        // dfs函数可以把 i 以及与 i 相连接的节点全部遍历一次
        // 没被遍历到的节点就一定在另个一个连通分量中
        dfs(i);
        ccount++;
      }
    }
  }

  ~Component()
  {
    delete[] visited, id;
  }

  // 查看该图有多少个连通分量
  int count()
  {
    return ccount;
  }

  // 查询两个节点是否相连（即是否在同一个连通分量内）
  // 虽然使用并查集查询两节点是否相连很容易，但要查询两节点相连的路径就很难了，下面就开始学图论算法！
  bool isConnected(int v, int w)
  {
    assert(v >= 0 && v < G.V());
    assert(w >= 0 && w < G.V());

    // 用 id 数组就很容易得知了
    return id[v] == id[w];
  }
};
