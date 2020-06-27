#include <cassert>
#include <iostream>

using namespace std;

namespace UF4
{
  // 并查集类
  class UnionFind
  {
  private:
    int *rank; // rank[i] 表示以 i 为根的集合所表示的数的层数（即有多少层）
    int *parent;
    int count;

  public:
    UnionFind(int c)
    {
      parent = new int[c];
      rank = new int[c];
      count = c;
      for (int i = 0; i < c; i++)
      {
        parent[i] = i;
        rank[i] = 1;
      }
    }

    ~UnionFind()
    {
      delete[] parent, rank;
    }

    // 寻找元素 p 的根
    int find(int p)
    {
      assert(p >= 0 && p < count);

      while (p != parent[p])
      {
        // 路径压缩优化关键代码！！只有一行
        parent[p] = parent[parent[p]]; // 往上条2个父结点

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

      // 本次优化只是在合并元素上
      // 应该每次合并时把层数少的节点指向层数多的去，这样多层的节点总层数就不会变
      // 只是加了优化判断...速度差了2 3个数量级...
      if (rank[pRoot] < rank[qRoot])
      {
        parent[pRoot] = qRoot;
      }
      else if (rank[qRoot] < rank[pRoot])
      {
        parent[qRoot] = pRoot;
      }
      else // rank[pRoot] == rank[qRoot]
      {
        parent[pRoot] = qRoot;
        rank[qRoot] += 1;
      }
    }
  };
} // namespace UF4
