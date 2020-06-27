#include "./Heap.h"

template <typename T>
void insertionSort(T arr[], int n)
{
  for (int i = 1; i < n; i++)
  {
    T e = arr[i];
    int j;
    for (j = i; j > 0 && arr[j - 1] > e; j--)
    {
      arr[j] = arr[j - 1];
    }
    arr[j] = e;
  }
}

// 对arr[l...r]范围内的数组元素进行插入排序
template <typename T>
void insertionSort(T arr[], int l, int r)
{
  for (int i = l + 1; i <= r; i++)
  {
    T e = arr[i];
    int j;
    for (j = i; j > l && arr[j - 1] > e; j--)
    {
      arr[j] = arr[j - 1];
    }
    arr[j] = e;
  }

  return;
}

template <typename T>
void __merge(T arr[], int l, int mid, int r)
{
  T aux[r - l + 1];
  for (int i = l; i <= r; i++)
  {
    aux[i - l] = arr[i];
  }

  int i = l, j = mid + 1;
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
  if (r - l <= 15)
  {
    insertionSort(arr, l, r);
    return;
  }

  int mid = (l + r) / 2;
  __mergeSort(arr, l, mid);
  __mergeSort(arr, mid + 1, r);

  if (arr[mid] > arr[mid + 1])
    __merge(arr, l, mid, r);
}

template <typename T>
void mergeSort(T arr[], int n)
{
  __mergeSort(arr, 0, n - 1);
}

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

