// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.20 08:48:42
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
namespace ringo {
template <class T> inline void read(T &x) {
    x = 0; register char c = getchar(); register bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
}
template <class T> inline void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }

const int N = 4e3 + 10;
int n, m, mod, ans, f[N][N], C[N][N];

void main() {
    read(n), read(mod), --n;
    for (int i = 0; i < N; i++) f[i][0] = 1;
    for (int k = 1; k < N; k++)
        for (int i = 0; i < N - 1; i++)
            f[i][k] = (ll)i * f[i + 1][k - 1] % mod;
    C[0][0] = 1;
    for (int i = 1; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = C[i - 1][j];
            if (j) C[i][j] = (C[i][j] + C[i - 1][j - 1]) % mod;
        }
    for (int i = 1, tmp = 1; i <= n; i++) {
        tmp = (ll)tmp * (i + 1) % mod;
        for (int x = 0; x <= n - i; x++) {
            ans = (ans + (ll)tmp * (x + 1) % mod * (n - x) % mod *
                C[n - i][x] % mod * f[2][x] % mod * f[i][n - i - x]) % mod;
        }
    }
    print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }