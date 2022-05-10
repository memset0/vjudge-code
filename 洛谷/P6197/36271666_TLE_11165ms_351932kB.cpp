#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 3e8 + 5;

int n, m, mod, ans, pn, a[30], pri[N / 10];
bool vis[N], ban[N];

inline int power(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = 1ll * x * x % mod) {
        if (y & 1) { res = 1ll * res * x % mod; }
    }
    return res;
}

void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            pri[++pn] = i;
            if (!ban[pn]) { ans = 1ll * ans * i % mod; }
        }
        for (int j = 1; j <= pn; j++) {
            int k = i * pri[j];
            if (k > n) { break; }
            vis[k] = true;
            if (i % pri[j] == 0) { break; }
        }
    }
}

int main() {
    n = read(); m = read(); mod = read();
    ans = 1; ban[1] = true;
    for (int i = 0; i < m; i++) {
        a[i] = read(); ban[a[i]] = true;
    }
    sieve(n);
    ans = (ans + mod - 1) % mod;
    for (int i = 0; i < m; i++) {
        if (a[i] == 1) { printf("-1\n"); return 0; }
        // int res = 1; mod = pri[a[i]];
        // for (int j = 1; j <= pn; j++) {
        //     if (!ban[j]) { res = 1ll * res * pri[j] % mod; }
        // }
        // if (res == 0) { printf("-1\n"); return 0; }
    }
    printf("%d\n", ans);
    return 0;
}