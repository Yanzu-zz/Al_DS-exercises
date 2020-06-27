#include <iostream>
#include "../SortTestHelper.h"

using namespace std;

template <typename T>
void selectionSort(T arr[], int n)
{
  for (int i = 0; i < n; i++)
  {
    int minIndex = i;

    for (int j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[minIndex])
      {
        minIndex = j;
      }
    }

    swap(arr[i], arr[minIndex]);
  }
}

/*
 * 如：（|前面代表已经确定当前位置的元素数组）
 * 8 | 6 2 3 1 5 7 4
 * 6 8 | 2 3 1 5 7 4
 * 6 2 8 | 3 1 5 7 4 > 2 6 8 | 3 1 5 7 4
 * 2 6 3 8 | 1 5 7 4 > 2 3 6 8 | 1 5 7 4
 * ···
 * 以此类推
*/
template <typename T>
void insertionSort(T arr[], int n)
{
  // 插入排序从第二个元素开始，故i=1
  for (int i = 1; i < n; i++)
  {
    // 寻找元素a[i]合适的插入位置
    // 从上面分析可以看到，未排序的数组是与前面排序过的数组相比，所以是从后往前
    /*for (int j = i; j > 0; j--)
    {
      // 不停地用 swap 操作很吃时间
      if (arr[j] < arr[j - 1])
        swap(arr[j], arr[j - 1]);
      else
        break;
    }*/

    // 代码优化版本
    T e = arr[i];
    int j; // 保存元素 e 应该插入的位置
    for (j = i; j > 0 && arr[j - 1] > e; j--)
    {
      arr[j] = arr[j - 1];
    }
    arr[j] = e;
  }
}

int main()
{
  int n = 100000;
  // 由于排序算法会改变原函数，所以我们需要复制多一份给第二个排序
  // int *arr = SortTestHelper::generateRandomArray(n, 0, n);
  int *arr = SortTestHelper::generateNearlyOrderedArray(n, 100);
  int *arr2 = SortTestHelper::copyIntArray(arr, n);

  // 对两种排序算法进行效率测试
  SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
  SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);

  delete[] arr, arr2;

  return 0;
}
