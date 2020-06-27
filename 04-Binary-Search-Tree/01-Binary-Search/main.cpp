// 二分查找法（对于有序数列，才能使用二分查找法）
#include <iostream>

using namespace std;

// 二分查找法，在有序数组 arr 中，查找 target
// 如果找到了 target，则返回对应的索引 index，无则返回 -1
template <typename T>
int binarySearch(T arr[], int n, int target)
{
  // 在 arr[l...r] 之中查找 target
  int l = 0, r = n - 1;

  // 一切都在这个循环内解决，没解决就是没有 target，则返回 -1
  while (l <= r)
  {
    // int mid = (l + r) / 2; 这样写可能会造成溢出
    int mid = l+(r-l)/2;
    if (arr[mid] == target)
    {
      return mid;
    }

    // 在 arr[l...mid-1] 之中查找 target
    if (target < arr[mid])
    {
      r = mid - 1;
    }
    else
    { // target > arr[mid]
      // 在 arr[mod+1...r] 之中查找 target
      l = mid + 1;
    }
  }

  return -1;
}

int main(void)
{

  return 0;
}
