// luogu-judger-enable-o2
#include <bits/stdc++.h>
int n, ans = 2;
int main() {
    std::cin >> n;
    for (int i = 2018; i >= n; i--)
        if (i % 4 == 3) ans = (ans + 5) % 7;
        else ans = (ans + 6) % 7;
    std::cout << 14 - ans << std::endl;
}