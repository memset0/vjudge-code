#include <bits/stdc++.h>

inline long long read() {
    char c; long long x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int mod = 998244353, w = 499122178;

inline int power(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = 1ll * x * x % mod) {
        if (y & 1) { res = 1ll * res * x % mod; }
    }
    return res;
}

long long n, ans;

int main() {
    for (int T = read(); T; T--) {
        n = read();
        ans = 1;
        ans += power(2, n % (mod - 1));
        ans += 2ll * power(w, n % (mod - 1));
        ans %= mod;
        printf("%lld\n", ans);
    }
    return 0;
}