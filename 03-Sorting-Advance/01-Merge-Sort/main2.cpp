// 自底向上实现归并排序

#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"

using namespace std;

template <typename T>
void mergeSortBU(T arr[], int n)
{
  for (int sz = 1; sz <= n; sz += sz)
  {
    // 判断 i+sz<n 是为了防止越界出错
    for (int i = 0; i + sz < n; i += sz + sz)
    {
      // 对 arr[i...i+sz-1] 和 arr[i+sz...i+2*sz-1] 进行归并
      // 这里的 min(xxx) 也是防止程序越界
      __merge(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1));
    }
  }
}

int main(void)
{

  return 0;
}
