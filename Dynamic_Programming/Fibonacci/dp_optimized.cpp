#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// 动态规划 —— 自下向上的解决问题
long long fib(int n) {
    vector<long long> memo(n + 1, -1);

    memo[0] = 0;
    memo[1] = 1;
    for (int i = 2; i <= n; i++)
        memo[i] = memo[i - 1] + memo[i - 2];

    return memo[n];
}

int main() {
    int n = 1000;

    time_t startTime = clock();
    long long res = fib(n);
    cout << "fib: " << res << endl;
    time_t endTime = clock();
    cout << "time: " << double(endTime - startTime) / CLOCKS_PER_SEC << endl;

    return 0;
}

