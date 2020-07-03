// Lazy Prim 算法优化，时间复杂度降低至 O(ElogV)
#include <vector>
#include <cassert>
#include "../Edge.h"
#include "../Graph.h"
#include "../IndexMinHeap.h"

using namespace std;

// MST —— Minimun Span Tree
template <typename Graph, typename Weight>
class PrimMST
{
private:
  Graph &G;
  vector<Edge<Weight> *> edgeTo;  // 存储最短的横切边
  IndexMinHeap<Weight> ipq; // priority queue heap
  bool *marked;                   // 标记某个节点是否被切分到另一分区
  Weight mstWeight;               // mst 最小权值
  vector<Edge<Weight>> mst;

  // 比之 Lazy Prim 算法就是我们这次的算法不会盲目的把所有边都加进堆中判断
  // 只有更小的才能加进来，这就大大减少了操作，提升了性能
  void visit(int v)
  {
    assert(!marked[v]);
    marked[v] = true;

    typename Graph::adjIterator adj(G, v);
    for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
    {
      // 找到 e 的邻边
      int w = e->other(v);
      if (!marked[w])
      {
        // 如果之前没有记录到该边的权值，直接记录即可
        if (!edgeTo[w])
        {
          ipq.insert(w, e->wt());
          edgeTo[w] = e;
        }
        // 如果记录过，则毕竟新旧两者的大小，小的放入 edgeTo 数组中
        else if (e->wt() < edgeTo[w]->wt())
        {
          edgeTo[w] = e;
          ipq.change(w, e->wt());
        }
      }
    }
  }

public:
  PrimMST(Graph &graph) : G(graph), ipq(IndexMinHeap<double>(graph.V()))
  {
    marked = new bool[G.V()];
    for (int i = 0; i < G.V(); i++)
    {
      marked[i] = false;
      edgeTo.push_back(NULL);
    }
    mst.clear();

    // Prim
    // 从节点0开始，逐个的将每个节点从蓝切分区转到红切分区（也可以是其他节点开始，这里我们就随便选了 0）
    visit(0);
    while (!ipq.isEmpty())
    {
      int v = ipq.extractMinIndex();
      assert(edgeTo[v]);

      mst.push_back(*edgeTo[v]);
      visit(v);
    }

    mstWeight = mst[0].wt();
    for (int i = 1; i < mst.size(); i++)
    {
      mstWeight += mst[i].wt();
    }
  }

  ~PrimMST()
  {
    delete[] marked;
  }

  vector<Edge<Weight>> mstEdges()
  {
    return mst;
  };

  // 返回最小权值结果
  Weight result()
  {
    return mstWeight;
  }
};
