#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int mod = 998244353;

const int N = 6e6 + 5;

int n, inv[N], f[N];

int main() {
    n = 6e6;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
    }
    for (int i = 1; i <= n; i++) {
        f[i] = (f[i - 1] + 1ll * inv[i] * inv[i]) % mod;
    }
    for (int T = read(); T; T--) {
        n = read();
        printf("%lld\n", 3ll * f[n] * inv[n] % mod);
    }
    return 0;
}
