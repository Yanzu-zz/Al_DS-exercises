#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

// 最大索引堆
template <typename Item>
class IndexMaxHeap
{
private:
  Item *data;
  int *indexes;
  Item *reverse;

  int count;
  int capacity;

  // 新添第k个元素上浮
  void shiftUp(int k)
  {
    // 有索引的地方就要注意越界问题
    while (k > 1 && data[indexes[k]] > data[indexes[k / 2]])
    {
      swap(indexes[k], indexes[k / 2]);
      reverse[indexes[k / 2]] = k / 2;
      reverse[indexes[k]] = k;
      k /= 2;
    }
  }

  // 第k个元素进行下沉
  void shiftDown(int k)
  {
    while (2 * k <= count)
    {
      int j = 2 * k; // 在此轮循环中，data[k] 和 data[j] 交换位置
      if (j + 1 <= count && data[indexes[j + 1]] > data[indexes[j]])
      {
        j += 1;
      }

      if (data[indexes[k]] >= data[indexes[j]])
      {
        break;
      }

      swap(indexes[k], indexes[j]);
      reverse[indexes[k]] = k;
      reverse[indexes[j]] = j;
      k = j;
    }
  }

public:
  IndexMaxHeap(int capacity)
  {
    data = new Item[capacity + 1];
    indexes = new int[capacity + 1];
    reverse = new Item[capacity + 1];
    for (int i = 0; i <= capacity; i++)
    {
      reverse[i] = 0;
    }

    count = 0;
    this->capacity = capacity;
  }

  IndexMaxHeap(Item arr[], int n)
  {
    // 先把传入数组的值一一赋值给data
    data = new Item[n + 1];
    capacity = n;
    for (int i = 0; i < n; i++)
    {
      data[i + 1] = arr[i];
    }
    count = n;

    // 接下来找到第一个非叶子结点的位置进行 Heapify（把数组转化为最大堆）操作
    for (int i = count / 2; i >= 1; i--)
    {
      shiftDown(i);
    }
  }

  // ~ 类的析构函数，在每次删除所创建的类时执行
  ~MaxHeap()
  {
    delete[] data, indexes, reverse;
  }

  int size()
  {
    return count;
  }

  bool isEmpty()
  {
    return count == 0;
  }

  // 往堆中添加一个元素并找到合适的位置
  // 传入的 i 对于用户而言，是从索引 0 开始的
  void insert(int i, Item item)
  {
    assert(count + 1 <= capacity);
    assert(i + 1 >= 1 && i + 1 <= capacity);

    i += 1;
    data[i] = item;
    indexes[count + 1] = i;
    reverse[i] = count + 1;
    count++;

    // 接下来就是对新加入的元素挪到合适的位置（即如比父结点值大/小的话）
    shiftUp(count);
  }

  Item extractMax()
  {
    assert(count > 0);

    Item ret = data[indexes[1]];
    swap(indexes[1], indexes[count]);
    reverse[indexes[1]] = 1;
    reverse[indexes[count]] = 0;
    count--;
    shiftDown(1);

    return ret;
  }

  int extractMaxIndex()
  {
    assert(count > 0);

    int ret = indexes[1] - 1;
    swap(indexes[1], indexes[count]);
    reverse[indexes[1]] = 1;
    reverse[indexes[count]] = 0;
    count--;
    shiftDown(1);

    return ret;
  }

  bool contain(int i)
  {
    assert(i + 1 >= 1 && i + 1 <= capacity);

    return reverse[i + 1] != 0;
  }

  Item getItem(int i)
  {
    assert(contain(i));

    return data[i + 1];
  }

  // 索引堆修改值函数
  void change(int i, Item newItem)
  {
    assert(contain(i));

    // 还是要注意用户传入的 i 的开始问题
    i += 1;
    data[i] = newItem;

    // 找到 indexes[j] = i，j 表示 data[j] 在堆中的位置
    // 之后 shiftUp(j)，再 shiftDown(j)
    /*for (int j = 1; j <= count; j++)
    {
      if (indexes[j] == i)
      {
        shiftUp(j);
        shiftDown(j);

        return;
      }
    }*/

    int j = reverse[i];
    shiftUp(j);
    shiftDown(j);
  }

public:
  void testPrint()
  {

    if (size() >= 100)
    {
      cout << "Fancy print can only work for less than 100 int";
      return;
    }

    if (typeid(Item) != typeid(int))
    {
      cout << "Fancy print can only work for int item";
      return;
    }

    cout << "The Heap size is: " << size() << endl;
    cout << "data in heap: ";
    for (int i = 1; i <= size(); i++)
      cout << data[i] << " ";
    cout << endl;
    cout << endl;

    int n = size();
    int max_level = 0;
    int number_per_level = 1;
    while (n > 0)
    {
      max_level += 1;
      n -= number_per_level;
      number_per_level *= 2;
    }

    int max_level_number = int(pow(2, max_level - 1));
    int cur_tree_max_level_number = max_level_number;
    int index = 1;
    for (int level = 0; level < max_level; level++)
    {
      string line1 = string(max_level_number * 3 - 1, ' ');

      int cur_level_number = min(count - int(pow(2, level)) + 1, int(pow(2, level)));
      bool isLeft = true;
      for (int index_cur_level = 0; index_cur_level < cur_level_number; index++, index_cur_level++)
      {
        putNumberInLine(data[index], line1, index_cur_level, cur_tree_max_level_number * 3 - 1, isLeft);
        isLeft = !isLeft;
      }
      cout << line1 << endl;

      if (level == max_level - 1)
        break;

      string line2 = string(max_level_number * 3 - 1, ' ');
      for (int index_cur_level = 0; index_cur_level < cur_level_number; index_cur_level++)
        putBranchInLine(line2, index_cur_level, cur_tree_max_level_number * 3 - 1);
      cout << line2 << endl;

      cur_tree_max_level_number /= 2;
    }
  }

private:
  void putNumberInLine(int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft)
  {

    int sub_tree_width = (cur_tree_width - 1) / 2;
    int offset = index_cur_level * (cur_tree_width + 1) + sub_tree_width;
    assert(offset + 1 < line.size());
    if (num >= 10)
    {
      line[offset + 0] = '0' + num / 10;
      line[offset + 1] = '0' + num % 10;
    }
    else
    {
      if (isLeft)
        line[offset + 0] = '0' + num;
      else
        line[offset + 1] = '0' + num;
    }
  }

  void putBranchInLine(string &line, int index_cur_level, int cur_tree_width)
  {

    int sub_tree_width = (cur_tree_width - 1) / 2;
    int sub_sub_tree_width = (sub_tree_width - 1) / 2;
    int offset_left = index_cur_level * (cur_tree_width + 1) + sub_sub_tree_width;
    assert(offset_left + 1 < line.size());
    int offset_right = index_cur_level * (cur_tree_width + 1) + sub_tree_width + 1 + sub_sub_tree_width;
    assert(offset_right < line.size());

    line[offset_left + 1] = '/';
    line[offset_right + 0] = '\\';
  }
};

int main(void)
{

  return 0;
}
