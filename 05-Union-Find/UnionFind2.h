#include <cassert>
#include <iostream>

using namespace std;

namespace UF2
{
  // 并查集类
  class UnionFind
  {
  private:
    int *parent;
    int count;

  public:
    UnionFind(int c)
    {
      parent = new int[c];
      count = c;
      for (int i = 0; i < c; i++)
      {
        parent[i] = i;
      }
    }

    ~UnionFind()
    {
      delete[] parent;
    }

    // 寻找元素 p 的根
    int find(int p)
    {
      assert(p >= 0 && p < count);

      while (p != parent[p])
      {
        p = parent[p];
      }

      return p;
    }

    bool isConnected(int p, int q)
    {
      return find(p) == find(q);
    }

    void unionElements(int p, int q)
    {
      int pRoot = find(p);
      int qRoot = find(q);

      if (pRoot == qRoot)
      {
        return;
      }

      parent[pRoot] = qRoot;
    }
  };
} // namespace UF2
