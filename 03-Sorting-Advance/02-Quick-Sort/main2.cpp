/*
 * 先找一个“基准数”，然后把他放到合适的位置（即前面的数比它小，后面比它大，这一步需要遍历一次数组）
*/
#include <iostream>
#include "../SortTestHelper.h"

using namespace std;

// 为基准数找到合适的位置并交换
// 即对 arr[l...r] 部分进行 partition 操作
// 返回索引p，使得 arr[l...p-1] < arr[p]；arr[p+1...r] > arr[p]
template <typename T>
T __partition(T arr[], int l, int r)
{
  // 随机选择一个基准数与第一个元素进行交换
  swap(arr[l], arr[rand() % (r - l + 1) + l]);

  T v = arr[l]; // 基准数

  // arr[l+1...i] <= v; arr[j...r) >= v
  int i = l + 1, j = r;
  while (true)
  {
    while (j >= l + 1 && arr[j] > v)
      j--;
    while (i <= r && arr[i] < v)
      i++;

    if (i > j)
      break;
    swap(arr[i], arr[j]);
    i++;
    j--;
  }

  swap(arr[l], arr[j]);

  return j;
}

// 对 arr[l...r] 部分进行快速排序
template <typename T>
void __quickSort(T arr[], int l, int r)
{
  if (r - l <= 15)
  {
    insertionSort(arr, l, r);
    return;
  }

  int p = __partition(arr, l, r);
  __quickSort(arr, l, p - 1); // 注意，p这个点是不用再排序的了
  __quickSort(arr, p + 1, r);
}

template <typename T>
void quickSort(T arr[], int n)
{
  srand(time(NULL));
  __quickSort(arr, 0, n - 1);
}

int main(void)
{
  int n = 1000001;
  cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
  int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
  int *arr2 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
  SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);

  delete[] arr1, arr2;

  // int swapTimes = 100;
  // cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
  // int *arr3 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
  // int *arr4 = SortTestHelper::copyIntArray(arr3, n);

  // SortTestHelper::testSort("Merge Sort", mergeSort, arr3, n);
  // SortTestHelper::testSort("Quick Sort", quickSort, arr4, n);

  // delete[] arr3, arr4;

  cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
  int *arr3 = SortTestHelper::generateRandomArray(n, 0, 10);
  int *arr4 = SortTestHelper::copyIntArray(arr3, n);

  SortTestHelper::testSort("Merge Sort", mergeSort, arr3, n);
  SortTestHelper::testSort("Quick Sort", quickSort, arr4, n);

  delete[] arr3, arr4;

  return 0;
}
