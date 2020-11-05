#include <bits/stdc++.h>

int a[20];
int main() {
    int n, min = 1e3;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
        min = std::min(min, a[i]);
    } 
    std::cout << 2 + (min ^ a[3]) << std::endl;
}
