// Lazy Prim 算法，时间复杂度为 O(ElogE)
#include <vector>
#include "../Graph.h"
#include "../MinHeap.h"

using namespace std;

// MST —— Minimun Span Tree
template <typename Graph, typename Weight>
class LazyPrimMST
{
private:
  Graph &G;
  MinHeap<Edge<Weight>> pq; // priority queue heap
  bool *marked;             // 标记某个节点是否被切分到另一分区
  Weight mstWeight;         // mst 最小权值
  vector<Edge<Weight>> mst;

  // 访问一个未切分的节点随后把该节点的边全部加入待定最小堆
  void visit(int v)
  {
    assert(!marked[v]);

    // 当访问到一个新的节点时，分到红且分区并标记已访问
    marked[v] = true;

    // 利用之前写好的图的迭代算法将顶点 v 的所有边都加入最小堆中
    typename Graph::adjIterator adj(G, v);
    for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
    {
      // 判断这条边另一方向的顶点是否切分过
      if (!marked[e->other(v)])
      {
        // 若无，则把该边加入到最小堆中
        pq.insert(*e);
      }
    }
  }

public:
  LazyPrimMST(Graph &graph) : G(graph), pq(MinHeap<Edge<Weight>>(graph.E()))
  {
    marked = new bool[G.V()];
    for (int i = 0; i < G.V(); i++)
    {
      marked[i] = false;
    }
    mst.clear();

    // Lazy Prim
    // 从节点0开始，逐个的将每个节点从蓝切分区转到红切分区（也可以是其他节点开始，这里我们就随便选了 0）
    visit(0);

    while (!pq.isEmpty())
    {
      Edge<Weight> e = pq.extractMin();

      // 判断该边是否为横切边
      // 即判断这条边两顶点是否在不同切分区
      if (marked[e.v()] == marked[e.w()])
      {
        // 不是的话不用管，跳过即可
        continue;
      }

      // 如果为横切边的话，加入最小堆等待比较最小权值的边
      mst.push_back(e);
      // 判断此条横切边哪边是待加入的
      // 横切边一边已切分一边未，这里只是简单判断下然后加入
      if (!marked[e.v()])
      {
        visit(e.v());
      }
      else
      {
        visit(e.w());
      }
    }

    // 初始化为最小生成树数组第一个元素的权值
    mstWeight = mst[0].wt();
    for (int i = 1; i < mst.size(); i++)
    {
      // 随后把剩下元素的权值都加上，结果就是最小权值
      mstWeight += mst[i].wt();
    }
  }

  ~LazyPrimMST()
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
