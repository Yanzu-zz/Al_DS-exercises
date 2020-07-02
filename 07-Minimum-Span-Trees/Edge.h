#ifndef EDGE_H
#define EDGE_H

#include <iostream>

using namespace std;

template <typename Weight> // 权值的类型模版
class Edge                 // 存储单个有权边的信息类，注意，是边
{
private:
  // 我们设计的这个节点信息类是可以同时处理有向和无向图的
  // 所以当图为有向图是，指明是 a→b，而无向图方向无所谓
  int a, b;
  Weight weight;

public:
  Edge(int a, int b, Weight weight)
  {
    this->a = a;
    this->b = b;
    this->weight = weight;
  }

  Edge() {}

  ~Edge() {}

  // 获取这个边的两个顶点以及相应的权值
  int v() { return a; }
  int w() { return b; }
  Weight wt() { return weight; }

  // 返回该边的另外一个顶点
  int other(int x)
  {
    assert(x == a || x == b);
    return x == a ? b : a;
  }

  // 重载 Edge <<符号，方便输出信息
  friend ostream &operator<<(ostream &os, const Edge &e)
  {
    // 重载 << 符号
    os << e.a << "-" << e.b << " : " << e.weight;
    return os;
  }

  // 我们经常会对边的两个顶点进行比较
  // 因此我们把比较运算符也重载一下
  bool operator<(Edge<Weight> &e)
  {
    return weight < e.wt();
  }
  bool operator<=(Edge<Weight> &e)
  {
    return weight <= e.wt();
  }

  bool operator>(Edge<Weight> &e)
  {
    return weight > e.wt();
  }
  bool operator>=(Edge<Weight> &e)
  {
    return weight >= e.wt();
  }

  bool operator==(Edge<Weight> &e)
  {
    return weight == e.wt();
  }
};

#endif /* EDGE_H */
