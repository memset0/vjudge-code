// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.11 14:41:05
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

const int N = 110;
const double eps = 1e-8;
int n, s, e;

inline double isap() {
    u = s;
    while (1) {

    }
}

inline bool check(double x) {
    tot = 2, memset(hed, 0, sizeof(hed));
    s = (n << 1) | 1, e = n + 1 << 1;
    for (int i = 1; i <= n; i++) add_edge(s, i, 1, 0), add_edge(i, e, 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            add_edge(i, j, 1, a[i][j] - x * b[i][j]);
    double sum = 0;
    while (spfa()) {
        
    }
    return isap() >= 0;
}

void main() {
    read(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            read(a[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            read(b[i][j]);
    l = 0, r = 1000000;
    while (r - l > eps) {
        mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    printf("%d.%06d\n", (int)mid, (int)((mid - (int)mid) * 1000000 + 0.5));
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}