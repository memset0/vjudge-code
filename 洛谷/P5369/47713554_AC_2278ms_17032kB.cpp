// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.20 20:37:22
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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

const int N = 25, M = 1 << 20, mod = 998244353;
int n, ans;
bool flag;
int a[N], id[N], f[M], g[M], t[M], sum[M];

template <class T> inline void sumd(int &a, T b) { a = (a + b) % mod; }

void main() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]), id[i] = 1 << (i - 1);
    }
    f[0] = g[0] = 1;
    for (int x = 0; x < (1 << n); x++) {
        for (int i = 1; i <= n; i++)
            if (x & id[i]) sum[x] += a[i];
    }
    flag = sum[(1 << n) - 1] < 0;
    for (int x = 0; x < (1 << n); x++) {
        for (int i = 1, y; i <= n; i++)
            if (!(x & id[i])) {
                y = x | id[i];
                sumd(t[y], f[x]);
                if (sum[y] > 0) sumd(f[y], f[x]);
                if (sum[y] <= 0) sumd(g[y], g[x]);
            }
    }
    // for (int x = 0; x < (1 << n); x++)
    // 	printf(">>> %d %d %d %d\n", x, sum[x], f[x], g[x]);
    for (int x = 0, y; x < (1 << n); x++) {
        y = ((1 << n) - 1) ^ x;
        sumd(ans, (ll)t[x] * g[y] % mod * sum[x]);
    }
    print((ans + mod) % mod, '\n');
}

} signed main() { return ringo::main(), 0; }