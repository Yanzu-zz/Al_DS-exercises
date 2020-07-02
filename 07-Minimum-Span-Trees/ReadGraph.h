#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

// 后续学习中我们都将图的方法封装在类中，这是因为通常对于一个图的算法而言会比较复杂
// 所以需要很多辅助的数据结构，这些数据结构都会相应的称为类中的变量
// 我们在描述算法思维的时候，不一定要写成类的结构，但是为了更好的学习和复用，这样最佳

// 图的算法可以根据传入的图的类型（稀疏/稠密）自动运算
template <typename Graph, typename Weight>
class ReadGraph
{
private:
public:
  ReadGraph(Graph &graph, const string &filename)
  {
    int V, E; // 此次读取的数据有多少个顶点和多少条边相通
    string line;
    ifstream file(filename);

    assert(file.is_open());

    assert(getline(file, line)); // 将需要读取的文件的第一行数据赋值给 line 变量
    stringstream ss(line);
    ss >> V >> E; // 再把值赋值给 顶点V 和边E（因为输入格式我们定义好了 A B）

    // 我们定义的图在初始化的时候就确定了点的数量，所以需要判断下读取的数量是否一致
    assert(V == graph.V());

    for (int i = 0; i < E; i++)
    {
      assert(getline(file, line));
      stringstream ss(line);

      int a, b;
      Weight w;
      ss >> a >> b >> w;
      assert(a >= 0 && a < V);
      assert(b >= 0 && b < V);

      // 在读入的 a b 都合法后，进行连边操作
      graph.addEdge(a, b, w);
    }
  }

  ~ReadGraph(){};
};
