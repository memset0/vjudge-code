// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.02 16:46:41
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

const int N = 4e2 + 10, mod = 1e9 + 7;
int n, ans, f[2][N][N], calc[N];

inline void sumd(int &a, int b) { a += b; if (a >= mod) a -= mod; }

void main() {
    read(n), f[0][1][1] = 1;
    for (register int i = 1; i <= n; i++) calc[i] = i * (i - 1);
    for (register int i = 0, u, v; i <= calc[n]; i++) {
        ans = 0, u = i & 1, v = u ^ 1;
        memset(f[v], 0, sizeof(f[v]));
        int limit = std::min(i + 1, n);
        for (register int j = 1; j <= limit; j++)
            for (register int k = j; k <= limit; k++) {
                if (!f[u][j][k]) continue;
                if (i <= j + k - 2 && k < n)
                    sumd(f[v][j][k + 1], f[u][j][k]);
                else if (calc[j] / 2 + calc[k] / 2 >= i + 1) 
                    sumd(f[v][j][k], f[u][j][k]);
                for (int t = 1; t <= k - j; t++)
                    if (calc[k] / 2 + calc[j + t] / 2 >= i + 1)
                        sumd(f[v][j + t][k], f[u][j][k]);
                sumd(ans, f[u][j][k]);
            }
        if (i) print(ans, ' ');
    }
}

} signed main() { return ringo::main(), 0; }