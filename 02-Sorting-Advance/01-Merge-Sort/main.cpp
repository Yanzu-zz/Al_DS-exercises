// 自顶向下实现归并排序

#include <iostream>
#include "../SortTestHelper.h"

using namespace std;

// 将 arr[l...mid]和arr[mid+1...r] 两部分进行归并
template <typename T>
void __merge(T arr[], int l, int mid, int r)
{
  // 复制一个一样的辅助数组空间进行下面的合并操作
  T aux[r - l + 1];
  for (int i = l; i <= r; i++)
  {
    aux[i - l] = arr[i];
  }

  // 合并辅助索引变量，从两边的最左边开始
  int i = l, j = mid + 1;
  // 开始合并
  for (int k = l; k <= r; k++)
  {
    if (i > mid)
    {
      arr[k] = aux[j - l];
      j++;
    }
    else if (j > r)
    {
      arr[k] = aux[i - l];
      i++;
    }
    else if (aux[i - l] < aux[j - l])
    {
      arr[k] = aux[i - l];
      i++;
    }
    else
    {
      arr[k] = aux[j - l];
      j++;
    }
  }
}

// 递归使用归并排序，对 arr[l...r] 的范围进行排序
template <typename T>
void __mergeSort(T arr[], int l, int r)
{
  // 递归函数第一行永远是判断边界
  // if (l >= r)
  //   return;

  // 当归并数组小于一定元素时，转用插入排序
  if (r - l <= 15)
  {
    insertionSort(arr, l, r);
    return;
  }

  int mid = (l + r) / 2;
  // 对左右分别进行排序
  __mergeSort(arr, l, mid);
  __mergeSort(arr, mid + 1, r);

  // 合并左右排序好的数组
  if (arr[mid] > arr[mid + 1])
    __merge(arr, l, mid, r);
}

template <typename T>
void mergeSort(T arr[], int n)
{
  __mergeSort(arr, 0, n - 1);
}

int main(void)
{
  int n = 100000;
  cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
  int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
  int *arr2 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
  SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);

  delete[] arr1, arr2;

  int swapTimes = 10;
  cout << "Test for Random Nearyly Ordered Array, size = " << n << ", random range [0, " << n << "]" << endl;
  int *arr3 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
  int *arr4 = SortTestHelper::copyIntArray(arr3, n);

  SortTestHelper::testSort("Insertion Sort", insertionSort, arr3, n);
  SortTestHelper::testSort("Merge Sort", mergeSort, arr4, n);

  delete[] arr3, arr4;

  return 0;
}
