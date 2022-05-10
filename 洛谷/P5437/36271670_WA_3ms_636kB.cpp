// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.06.29 16:20:49
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
    x = 0; char c = getchar(); bool f = 0;
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
    if (s != "") std::cout << s << ": ";
    for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 100;
int n, cnt;
bool f[N][N], ans[N][N];

void main() {
    read(n);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            (i & j) ? (ans[j][i] = 1) : (ans[i][j] = 1);
    for (int i = 1; i + 2 <= n; i += 2) ans[i + 2][i] = 1;
    ans[2][n & 1 ? n : n - 1] = 1;
    for (int i = 2; i + 2 <= n; i += 2) ans[i + 2][i] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            f[i][j] = ans[i][j];
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                f[i][j] |= f[i][k] & f[k][j];
    for (int a = 1; a <= n; a++)
        for (int b = a + 1; b <= n; b++)
            for (int c = b + 1; c <= n; c++)
                for (int d = c + 1; d <= n; d++)
                    if (f[a][b] && f[a][c] && f[a][d] && f[b][c] && f[b][d] && f[c][d])
                        ++cnt;
    print(cnt, '\n');
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            print(ans[i][j], " \n"[j == n]);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}