// 给定一个数组，我们把数组的排列形成一个堆的形状，这就是 Heapify
#include <cmath>
#include <cassert>
#include <iostream>
#include "../Heap.h"
#include "../SortTestHelper.h"

using namespace std;

// 第一版堆排序
template <typename T>
void heapSort1(T arr[], int n)
{
  MaxHeap<T> maxheap = MaxHeap<T>(n);
  for (int i = 0; i < n; i++)
  {
    maxheap.insert(arr[i]);
  }

  for (int i = n - 1; i >= 0; i--)
  {
    arr[i] = maxheap.extractMax();
  }
}

// Heapify
template <typename T>
void heapSort2(T arr[], int n)
{
  MaxHeap<T> maxheap = MaxHeap<T>(arr, n);

  for (int i = n - 1; i >= 0; i--)
  {
    arr[i] = maxheap.extractMax();
  }
}

int main(void)
{
  int n = 1000000;

  // 测试1 一般性测试
  cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
  int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
  int *arr2 = SortTestHelper::copyIntArray(arr1, n);
  int *arr3 = SortTestHelper::copyIntArray(arr1, n);
  int *arr4 = SortTestHelper::copyIntArray(arr1, n);
  int *arr5 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
  SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
  SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr3, n);
  SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);
  SortTestHelper::testSort("Heap Sort 2", heapSort2, arr5, n);

  delete[] arr1, arr2, arr3, arr4;
  cout << endl;

  // 测试2 测试近乎有序的数组
  int swapTimes = 100;
  arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
  arr2 = SortTestHelper::copyIntArray(arr1, n);
  arr3 = SortTestHelper::copyIntArray(arr1, n);
  arr4 = SortTestHelper::copyIntArray(arr1, n);
  arr5 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
  SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
  SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr3, n);
  SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);
  SortTestHelper::testSort("Heap Sort 2", heapSort2, arr5, n);

  delete[] arr1, arr2, arr3, arr4;
  cout << endl;

  // 测试3 测试存在包含大量相同元素的数组
  arr1 = SortTestHelper::generateRandomArray(n, 0, 10);
  arr2 = SortTestHelper::copyIntArray(arr1, n);
  arr3 = SortTestHelper::copyIntArray(arr1, n);
  arr4 = SortTestHelper::copyIntArray(arr1, n);
  arr5 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
  SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
  SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr3, n);
  SortTestHelper::testSort("Heap Sort 1", heapSort1, arr4, n);
  SortTestHelper::testSort("Heap Sort 2", heapSort2, arr5, n);

  delete[] arr1, arr2, arr3, arr4;
  cout << endl;

  return 0;
}
