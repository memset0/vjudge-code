#include <bits/stdc++.h>

int main() {
    long long n, m, p;
    std::cin >> n >> m >> p;
    long long s = 1;
    for (; p; p >>= 1, n = (long long)n * n % m)
        if (p & 1) s = (long long)s * n % m;
    std::cout << s << std::endl;
}