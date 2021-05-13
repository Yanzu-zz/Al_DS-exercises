#include <iostream>
#include <ctime>

using namespace std;

int num = 0;

// 最初版本斐波那契，时间复杂度为 O(2^n)
int fib_origin(int n) {
    num++;
    if (n == 0 || n == 1)
        return 1;

    return fib_origin(n - 1) + fib_origin(n - 2);
}

int main() {
    int n = 40;

    time_t startTime = clock();
    int res = fib_origin(n);
    cout << "fib: " << res << endl;
    time_t endTime = clock();
    cout << "time: " << double(endTime - startTime) / CLOCKS_PER_SEC << endl;
    cout << "run fun fib() " << num << " times." << endl;

    return 0;
}