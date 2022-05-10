// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.11 21:51:08
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

const int N = 25010, M = 1e5 + 10;
int n, x, y, ans, a[N], b[N], cnt[M];

void main() {
    read(n), read(x), read(y);
    for (int i = 1; i <= n; i++) {
        read(a[i]), read(b[i]);
        ++cnt[a[i]], --cnt[b[i]];
    }
    for (int i = 0; i < M; i++) {
        if (cnt[i] > 0) ans += cnt[i] * x;
        if (cnt[i] < 0) ans -= cnt[i] * y;
        if (i != M - 1) cnt[i + 1] += cnt[i];
    }
    print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }