// 3路快速排序法 Quick Sort 3 Ways
// 和平常的快排比就多了个 == v 区域
#include <iostream>
#include <algorithm>
#include "../SortTestHelper.h"

using namespace std;

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


// 三路快速排序处理 arr[l...r]
// 将 arr[l...r] 分为 <v; ==v; >v 三部分
// 之后递归对 <v; >v 两部分继续进行三路快排
template <typename T>
void __quickSort3Ways(T arr[], int l, int r)
{
  if (r - l <= 15)
  {
    insertionSort(arr, l, r);
    return;
  }

  // partition
  swap(arr[l], arr[rand() % (r - l + 1) + l]);
  T v = arr[l];

  int lt = l;     // arr[l+1...lt] < v
  int gt = r + 1; // arr[gt...r] > v
  int i = l + 1;  // arr[lt+1...i] == v
  while (i < gt)
  {
    if (arr[i] < v)
    {
      swap(arr[i], arr[lt + 1]);
      lt++;
      i++;
    }
    else if (arr[i] > v)
    {
      swap(arr[i], arr[gt - 1]);
      gt--;
      // 这里 i 指针不用动，因为当前元素与后面的交换了，是新的元素，需要判断
    }
    else
    { // arr[i] == v
      // 这里不用动，判断下一个元素即可，自然会形成一个 ==v 区域
      i++;
    }
  }

  swap(arr[l], arr[lt]); // 把基准值放到合适的位置

  // 继续对剩下的数组进行递归
  // 这里很明显的少处理了中间 ==v 区域，只用处理前、后两个区域
  __quickSort3Ways(arr, l, lt - 1);
  __quickSort3Ways(arr, gt, r);
}

template <typename T>
void quickSort3Ways(T arr[], int n)
{
  srand(time(NULL));
  __quickSort3Ways(arr, 0, n - 1);
}

int main(void)
{
  int n = 100000;
  cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
  int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
  int *arr2 = SortTestHelper::copyIntArray(arr1, n);
  int *arr2_1 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("Merge Sort", mergeSort, arr1, n);
  SortTestHelper::testSort("Quick Sort", quickSort, arr2, n);
  SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr2_1, n);

  delete[] arr1, arr2;

  int swapTimes = 50;
  cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
  int *arr3 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
  int *arr4 = SortTestHelper::copyIntArray(arr3, n);
  int *arr4_1 = SortTestHelper::copyIntArray(arr3, n);

  SortTestHelper::testSort("Merge Sort", mergeSort, arr3, n);
  SortTestHelper::testSort("Quick Sort", quickSort, arr4, n);
  SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr4_1, n);

  delete[] arr3, arr4;

  cout << "Test for Random Array, size = " << n << ", random range [0, " << n << "]" << endl;
  int *arr5 = SortTestHelper::generateRandomArray(n, 0, 10);
  int *arr6 = SortTestHelper::copyIntArray(arr5, n);
  int *arr6_1 = SortTestHelper::copyIntArray(arr5, n);

  SortTestHelper::testSort("Merge Sort", mergeSort, arr3, n);
  SortTestHelper::testSort("Quick Sort", quickSort, arr6, n);
  SortTestHelper::testSort("Quick Sort 3 Ways", quickSort3Ways, arr6_1, n);

  delete[] arr5, arr6;

  return 0;
}
