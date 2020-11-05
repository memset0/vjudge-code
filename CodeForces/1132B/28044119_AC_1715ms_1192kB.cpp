#include <bits/stdc++.h>

const int N = 3e5 + 10;
int a[N];
bool cmp(int a, int b) { return a > b; }

int main() {
    int n, i, m, q, minq = 1e9;
    long long sum = 0;
    std::cin >> n;
    for (i = 1; i <= n; i++) std::cin >> a[i], sum += a[i];
    std::cin >> m;
    std::sort(a + 1, a + n + 1, cmp);
    for (i = 1; i <= m; i++) std::cin >> q, std::cout << sum - a[q] << std::endl;
    return 0;
}