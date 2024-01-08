// =================================
//   author: memset0
//   date: 2019.03.20 21:58:38
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

const int N = 10;
int n, m, ans = true, a[N][N];

void main() {
    read(n), read(m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char c = getchar();
            while (c != '#' && c != '.') c = getchar();
            a[i][j] = c == '#';
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j]) {
                if (i != n && j != m) {
                    if (a[i + 1][j] && a[i][j + 1])
                        ans = false;
                    if (!a[i + 1][j] && !a[i][j + 1])
                        ans = false;
                }
                if (i != 1 || j != 1) {
                    if (a[i - 1][j] && a[i][j - 1])
                        ans = false;
                    if (!a[i - 1][j] && !a[i][j - 1])
                        ans = false;
                }
            }
    puts(ans ? "Possible" : "Impossible");
}

} signed main() { return ringo::main(), 0; }