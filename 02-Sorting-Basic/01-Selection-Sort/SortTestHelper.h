#include <ctime>
#include <iostream>
#include <cassert>

using namespace std;

namespace SortTestHelper
{
  // 生成有n个元素的随机数组，每个元素的随机范围为 [rangeL, rangeR]
  int *generateRandomArray(int n, int rangeL, int rangeR)
  {
    assert(rangeL <= rangeR);

    int *arr = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++)
      arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;

    return arr;
  }

  template <typename T>
  void printArray(T arr[], int n)
  {
    for (int i = 0; i < n; i++)
      cout << arr[i] << " ";
    cout << endl;

    return;
  }

  /*
   * testSort 测试排序函数执行时间函数
   * @param sortName：               需要测试的排序函数名，用来输出提示
   * @param void(*sort)(T[], int n)  排序函数，格式是同一的
   * @param arr[]                    传入的测试数组
   * @param n                        测试数组的长度
  */
  template <typename T>
  void testSort(string sortName, void (*sort)(T[], int n), T arr[], int n)
  { 
  }
} // namespace SortTestHelper
