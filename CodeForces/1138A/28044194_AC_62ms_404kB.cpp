#include <bits/stdc++.h>

const int N = 1e5 + 6;
int n, x, y, ans, z = -1, a[N];

int main() {
    std::cin >> n;
    for (int i = 1; i <= n + 1; i++) {
        if (i != n + 1) std::cin >> a[i];
        if (--a[i] != z && i != 1) {
            ans = std::max(ans, 2 * std::min(y, x));
            y = x, x = 0;
        } x++, z = a[i];
    }
    std::cout << ans << std::endl;
}