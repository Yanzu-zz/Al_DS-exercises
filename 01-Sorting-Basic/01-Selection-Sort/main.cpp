#include <iostream>
#include <algorithm>
#include "Student.h"
#include "../SortTestHelper.h"

using namespace std;

// 选择排序算法
/*
 * 如：（|前面代表已经确定当前位置的元素数组）
 * 8 6 2 3 1 5 7 4   （当前需要交换的元素位置是 [0]，即 8）
 * 1 | 6 2 3 8 5 7 4 （当前需要交换的元素位置是 [1]，即 6）
 * 1 2 | 6 3 8 5 7 4  ···
 * 1 2 3 | 6 8 5 7 4
 * 1 2 3 4 | 8 5 7 4
 * ···
 * 以此类推
*/
template <typename T>
void selectionSort(T arr[], int n)
{
  // 寻找 [i, n) 区间里的最小值，这里假定要求是从小到大排序
  for (int i = 0; i < n; i++)
  {
    // 每次循环需要找的“剩下未排序元素”的索引变量
    int minIndex = i;

    // 开始寻找本轮需要找的最小元素，从“剩下未排序元素数组”的第一个元素开始，故为 i+1
    for (int j = i + 1; j < n; j++)
    {
      if (arr[j] < arr[minIndex]){
        minIndex = j; // 寻找操作
      }
    }
    // 在扫描完一次 剩下待排序数组 后，交换
    swap(arr[i], arr[minIndex]);
  }
}

int main(void)
{
  int an = 10000;
  int *arr1 = SortTestHelper::generateRandomArray(an, 0, an);
  // SortTestHelper::printArray(arr1, an);
  // selectionSort(arr1, an);
  // SortTestHelper::printArray(arr1, an);
  SortTestHelper::testSort("Selection Sort", selectionSort, arr1, an);

  /* int bn = 5;
  int *arr2 = SortTestHelper::generateRandomArray(bn, 0, bn);
  selectionSort(arr2, bn);
  SortTestHelper::printArray(arr2, bn);

  // struct 结构也能排序哦
  Student c[4] = {{"D", 90}, {"C", 100}, {"B", 80}, {"A", 95}};
  selectionSort(c, 4);
  for (int i = 0; i < 4; i++)
    cout << c[i];
  cout << endl;
  */

  return 0;
}
