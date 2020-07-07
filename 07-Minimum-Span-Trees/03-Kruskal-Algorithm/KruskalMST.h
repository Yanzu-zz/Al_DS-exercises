#include <iostream>
#include <vector>
#include "../Edge.h"
#include "../MinHeap.h"
#include "../UnionFind.h"

using namespace std;

template <typename Graph, typename Weight>
class KruskalMST
{
private:
  vector<Edge<Weight>> mst;
  Weight mstWeight;

public:
  KruskalMST(Graph &graph)
  {
    // cout<< graph.E() << endl;
    MinHeap<Edge<Weight>> pq(graph.E());

    // 使用堆这个结构是因为可以排序又可以提取最小值
    for (int i = 0; i < graph.V(); i++)
    {
      typename Graph::adjIterator adj(graph, i);
      for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
      {
        // 因为我们这用的是无向图，所以只对 1->2 放入堆中，2->1 的就无视
        if (e->v() < e->w())
        {
          pq.insert(*e);
        }
      }
    }

    UnionFind uf(graph.V());
    while (!pq.isEmpty() && mst.size() < graph.V() - 1)
    {
      Edge<Weight> e = pq.extractMin();

      // 使用并查集来判断要新加入的切分节点会不会形成环
      // 当最小生成树已经生成，剩下的节点就不用看了，直接退出
      if (uf.isConnected(e.v(), e.w()))
      {
        continue;
      }

      mst.push_back(e);
      uf.unionElements(e.v(), e.w());
    }

    // 计算最小生成树最小权值
    mstWeight = mst[0].wt();
    for (int i = 1; i < mst.size(); i++)
    {
      mstWeight += mst[i].wt();
    }
  }

  ~KruskalMST()
  {
  }

  vector<Edge<Weight>> mstEdges()
  {
    return mst;
  };

  Weight result()
  {
    return mstWeight;
  }
};
