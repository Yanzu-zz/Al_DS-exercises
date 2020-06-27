#include <ctime>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include "Sorts.h"

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

  // 生成近乎有序随机数组函数
  int *generateNearlyOrderedArray(int n, int swapTimes)
  {
    int *arr = new int[n];
    // 先生成一个有序数组
    for (int i = 0; i < n; i++)
    {
      arr[i] = i;
    }

    // 再随机挑选几个元素进行交换，这样我们生成的数组就近乎有序了
    srand(time(NULL));
    for (int i = 0; i < swapTimes; i++)
    {
      int posx = rand() % n;
      int posy = rand() % n;
      swap(arr[posx], arr[posy]);
    }

    return arr;
  }

  // 简单打印输出辅助函数
  template <typename T>
  void printArray(T arr[], int n)
  {
    for (int i = 0; i < n; i++)
      cout << arr[i] << " ";
    cout << endl;

    return;
  }

  // 判断执行完排序算法后结果是否正确辅助函数
  template <typename T>
  bool isSorted(T arr[], int n)
  {
    for (int i = 0; i < n - 1; i++)
    {
      if (arr[i] > arr[i + 1])
      {
        return false;
      }
    }

    return true;
  }

  /*
   * testSort 测试排序函数执行时间函数
   * @param sortName：               需要测试的排序函数名，用来输出提示
   * @param void(*sort)(T[], int n)  排序函数，格式是同一的
   * @param arr[]                    传入的测试数组
   * @param n                        测试数组的长度
  */
  template <typename T>
  void testSort(string sortName, void (*sort)(T[], int), T arr[], int n)
  {
    // 用开始时间-结束时间
    clock_t startTime = clock();
    sort(arr, n);
    clock_t endTime = clock();

    assert(isSorted(arr, n));
    cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;

    return;
  }

  int *copyIntArray(int a[], int n)
  {
    int *arr = new int[n];
    copy(a, a + n, arr);

    return arr;
  }
} // namespace SortTestHelper
