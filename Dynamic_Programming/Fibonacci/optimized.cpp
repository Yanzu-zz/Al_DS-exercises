#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

vector<long long> memo; // 存储对应斐波那契计算后的值
int num = 0;

long long fib(int n) {
    num++;
    if (n == 0 || n == 1)
        return 1;

    // 用数组存储结果后就不用递归的查询指数次了
    if (memo[n] == -1)
        memo[n] = fib(n - 1) + fib(n - 2);
    return memo[n];
}

int main() {
    int n = 40;
    memo = vector<long long>(n + 1, -1);

    time_t startTime = clock();
    long long res = fib(n);
    cout << "fib: " << res << endl;
    time_t endTime = clock();
    cout << "time: " << double(endTime - startTime) / CLOCKS_PER_SEC << endl;
    cout << "run fun fib() " << num << " times." << endl;

    return 0;
}
