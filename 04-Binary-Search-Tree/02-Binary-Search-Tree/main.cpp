#include <queue>
#include <ctime>
#include <cassert>
#include <iostream>
#include <algorithm>
#include "../FileOps.h"
#include "../SequenceST.h"

using namespace std;

// 二叉查找树（Binary Search Tree）
template <typename Key, typename Value>
class BST
{
private:
  // 一个好的类的封装应该要对内部的实现结构对外隐藏
  struct Node
  {
    Key key;
    Value value;
    Node *left;
    Node *right;

    // struct 的构造函数
    Node(Key key, Value value)
    {
      this->key = key;
      this->value = value;
      this->left = this->right = NULL;
    }

    // 重写构造函数，作用为简单的复制一份传入的 node 节点所有值
    Node(Node *node)
    {
      this->key = node->key;
      this->value = node->value;
      this->left = node->left;
      this->right = node->right;
    }
  };

  Node *root;
  int count;

public:
  BST()
  {
    root = NULL;
    count = 0;
  }

  ~BST()
  {
    // 采用后序遍历的方式来逐个释放空间
    destory(root);
  }

  int size()
  {
    return count;
  }

  bool isEmpty()
  {
    return count == 0;
    // or return root==NULL;
  }

  void insert(Key key, Value value)
  {
    root = insert(root, key, value);
  }

  void insert_loop(Key key, Value value)
  {
    root = insert_loop(root, key, value);
  }

  // 判断该树是否包含 key，返回 是/否
  bool contain(Key key)
  {
    return contain(root, key);
  }

  // 这样设置函数返回类型的好处是不用担心对外暴露Node结构，且若查询不到 key 值，指针类型也可以为空
  // 当然也可以要求用户先 contain 查询一下再使用 search 函数，这样返回值可以直接为 Value
  Value *search(Key key)
  {
    return search(root, key);
  }

  /*
   * 二叉搜索树的遍历，分三种：前中后序遍历
   * 前序遍历：先访问当前节点，再依次递归访问左右子树；
   * 中序遍历：先递归访问左子树，再访问自身，再递归访问右子树；
   * 后序遍历：先递归访问左右子树，再访问自身节点。
   * （忘了的看网上文章或视频）
  */
  // 前序遍历（也是深度优先搜索）
  void preOrder()
  {
    preOrder(root);
    cout << endl;
  }

  // 中序遍历
  void inOrder()
  {
    inOrder(root);
  }

  // 后序遍历
  void postOrder()
  {
    postOrder(root);
  }

  // 层序遍历（即广度优先搜索）
  void levelOrder()
  {
    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
      Node *node = q.front();
      q.pop();

      cout << node->key << endl;

      if (node->left)
      {
        q.push(node->left);
      }

      if (node->right)
      {
        q.push(node->right);
      }
    }
  }

  // 寻找二叉搜索树最小的键值
  Key minimum()
  {
    assert(count != 0);
    Node *minNode = minimum(root);
    return minNode->key;
  }

  // 寻找二叉搜索树最大的键值
  Key maximum()
  {
    assert(count != 0);
    Node *maxNode = maximum(root);
    return maxNode->key;
  }

  // 从二叉树中删除最小值所在节点
  void removeMin()
  {
    if (root)
    {
      root = removeMin(root);
    }
  }

  // 从二叉树中删除最大值所在节点
  void removeMax()
  {
    if (root)
    {
      root = removeMax(root);
    }
  }

  // 从二叉树中删除指定键值 key 的节点
  void remove(Key key)
  {
    root = remove(root, key);
  }

  // 从二叉树中查找比 key 小又最接近的节点（无视key）
  Key floor(Key key)
  {
    assert(count != 0);
    Node *floorNode = floor(root, key);
    return floorNode->key;
  }

private: // 牵扯到 Node 的方法都是私有方法，不需要对外暴露结构的具体结构
  /*
   * （递归写法）向以 node 为根的二叉搜索树中，插入节点(key, value)
   * @param *node: 需要插入的二叉搜索树的（第一个是）根结点位置
   * @param key:   键
   * @param value: 值
   * @return 返回插入新节点后的二叉搜索树的根
  */
  Node *insert(Node *node, Key key, Value value)
  {
    if (node == NULL)
    {
      count++;
      return new Node(key, value);
    }

    if (key == node->key)
    {
      node->value = value;
    }
    else if (key < node->key)
    {
      node->left = insert(node->left, key, value);
    }
    else
    { // key > node->key
      node->right = insert(node->right, key, value);
    }

    return node;
  }

  // 非递归写法
  Node *insert_loop(Node *node, Key key, Value value)
  {
    // 只要没找到新元素应该插入的位置，就一直寻着链找下去
    while (node != NULL)
    {
      if (key == node->key)
      {
        node->value = value;
        // 如果是相同元素就返回当前元素的 node 信息
        return node;
      }
      else if (key < node->key)
      {
        node = node->left;
      }
      else
      {
        node = node->right;
      }
    }

    count++;
    return new Node(key, value);
  }

  // （递归）查看以 node 为根的二叉搜索树中是否包含键值为 key 的节点
  bool contain(Node *node, Key key)
  {
    if (node == NULL)
    {
      return false;
    }

    if (key == node->key)
    {
      return true;
    }
    else if (key < node->key)
    {
      return contain(node->left, key);
    }
    else
    {
      return contain(node->right, key);
    }
  }

  // 在以 node 为根的二叉搜索树中查找 key 所对应的 value
  Value *search(Node *node, Key key)
  {
    // 判断边界条件
    if (node == NULL)
    {
      return NULL;
    }

    if (key == node->key)
    {
      return &(node->value);
    }
    else if (key < node->key)
    {
      return search(node->left, key);
    }
    else
    {
      return search(node->right, key);
    }
  }

  // 对以 node 为根的二叉搜索树进行前序遍历
  void preOrder(Node *node)
  {
    if (node != NULL)
    {
      cout << node->key << " ";
      preOrder(node->left);
      preOrder(node->right);
    }
  }

  // 对以 node 为根的二叉搜索树进行中序遍历
  void inOrder(Node *node)
  {
    if (node != NULL)
    {
      inOrder(node->left);
      cout << node->key << endl;
      inOrder(node->right);
    }
  }

  // 对以 node 为根的二叉搜索树进行后序遍历
  void postOrder(Node *node)
  {
    if (node != NULL)
    {
      inOrder(node->left);
      inOrder(node->right);
      cout << node->key << endl;
    }
  }

  // 后序遍历方式释放整个二叉搜索树
  void destory(Node *node)
  {
    if (node != NULL)
    {
      destory(node->left);
      destory(node->right);
      delete node;
      count--;
    }
  }

  // 在以 node 为根的二叉搜索树中，返回最小键值的节点
  Node *minimum(Node *node)
  {
    if (node->left == NULL)
    {
      return node;
    }

    return minimum(node->left);
  }

  // 在以 node 为根的二叉搜索树中，返回最小键值的节点
  Node *maximum(Node *node)
  {
    if (node->right == NULL)
    {
      return node;
    }

    return maximum(node->right);
  }

  // 删除掉以 node 为根的二分搜索树中的最小节点
  // 返回删除节点后新的二分搜索树的根
  Node *removeMin(Node *node)
  {
    // 找到最小节点了
    if (node->left == NULL)
    {
      // 最小节点没有左子节点的可能
      Node *rightNode = node->right;

      delete node;
      count--;
      return rightNode;
    }

    node->left = removeMin(node->left);
    return node;
  }

  // 删除掉以 node 为根的二分搜索树中的最大节点
  // 返回删除节点后新的二分搜索树的根
  Node *removeMax(Node *node)
  {
    // 找到最大节点
    if (node->right == NULL)
    {
      Node *leftNode = node->left;

      delete node;
      count--;
      return leftNode;
    }

    node->right = removeMax(node->right);
    return node;
  }

  // 删除掉以 node 为根的二分搜索树中键值为 key 的节点
  // 返回删除节点后新的二分搜索树的根
  Node *remove(Node *node, Key key)
  {
    if (node == NULL)
    {
      return NULL;
    }

    if (key < node->key)
    {
      node->left = remove(node->left, key);
      return node;
    }
    else if (key->node->key)
    {
      node->right = remove(node->right, key);
      return node;
    }
    else // key == node->key
    {
      // 左孩子空的情况（即使此时右孩子也为空，返回 NULL 也合理）
      if (node->left == NULL)
      {
        Node *rightNode = node->right;
        delete node;
        count--;

        return rightNode;
      }

      // 右孩子为空的情况（上面判断过了，所以此时左孩子必定存在）
      if (node->right == NULL)
      {
        Node *leftNode = node->left;
        delete node;
        count--;

        return leftNode;
      }

      // 最麻烦的情境，左右孩子都存在的情况
      // node->left != NULL && node->right != NULL
      Node *successor = new Node(minimum(node->right)); // 找到要删除节点的右子树最小节点值做为继承节点
      count++;                                          // 下面的 removeMin 里 count 会--，所以这里记得要加上去

      successor->right = removeMin(node->right);
      successor->left = node->left;

      delete node;
      count--;

      return successor;
    }
  }

  // 从二叉树中查找比 key 小又最接近的节点（无视key）
  Node *floor(Node *node, Key key)
  {
    static Key refer = 0;
    static Node *retNode = NULL;

    if (node == NULL)
    {
      return retNode;
    }

    if (node->key < key)
    {
      if (refer == 0 || key - node->key < refer)
      {
        refer = key - node->key;
        retNode = new Node(node);
      }

      floor(node->right, key);
    }
    else if (node->key > key)
    {
      floor(node->left, key);
    }
    else
    {
      floor(node->left, key);
    }

    return node;
  }
};

int main(void)
{
  /*string filename = "../bible.txt";
  vector<string> words;
  if (FileOps::readFile(filename, words))
  {

    cout << "There are totally " << words.size() << " words in " << filename << endl;

    cout << endl;

    // test BST
    time_t startTime = clock();
    BST<string, int> bst = BST<string, int>();
    for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++)
    {
      int *res = bst.search(*iter);
      if (res == NULL)
        bst.insert(*iter, 1);
      else
        (*res)++;
    }

    cout << "'god' : " << *bst.search("god") << endl;
    time_t endTime = clock();
    cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;

    cout << endl;

    // test SST
    startTime = clock();
    SequenceST<string, int> sst = SequenceST<string, int>();
    for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++)
    {
      int *res = sst.search(*iter);
      if (res == NULL)
        sst.insert(*iter, 1);
      else
        (*res)++;
    }

    cout << "'god' : " << *sst.search("god") << endl;

    endTime = clock();
    cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
  }*/

  BST<int, int> bst = BST<int, int>();

  srand(time(NULL));
  for (int i = 0; i < 10; i++)
  {
    bst.insert(rand() % 100, rand() % 100);
  }

  bst.preOrder();

  // int result = bst.floor(50);
  // cout << result << endl;

  return 0;
}
