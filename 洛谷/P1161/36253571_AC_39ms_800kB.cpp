// luogu-judger-enable-o2
#include <bits/stdc++.h>

int n, t, ans;
double a;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin>>a>>t;
        for (int j = 1; j <= t; j++)
            ans ^= (int)(j * a);
    }
    std::cout << ans << std::endl;
}