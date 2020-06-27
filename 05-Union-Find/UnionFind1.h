#include <cassert>
#include <iostream>

using namespace std;

namespace UF1
{
  // 并查集类
  class UnionFind
  {
  private:
    int *id;
    int count;

  public:
    UnionFind(int n)
    {
      count = n;
      id = new int[n];
      for (int i = 0; i < n; i++)
      {
        id[i] = i;
      }
    }

    ~UnionFind()
    {
      delete[] id;
    }

    int find(int p)
    {
      assert(p >= 0 && p < count);

      return id[p];
    }

    // 判断两个点是否是连接状态
    bool isConnected(int p, int q)
    {
      return find(p) == find(q);
    }

    // 并上两个元素
    void unionElements(int p, int q)
    {
      int pID = find(p);
      int qID = find(q);

      if (pID == qID)
      {
        return;
      }

      for (int i = 0; i < count; i++)
      {
        if (id[i] == pID)
        {
          id[i] = qID;
        }
      }
    }
  };
} // namespace UF1
