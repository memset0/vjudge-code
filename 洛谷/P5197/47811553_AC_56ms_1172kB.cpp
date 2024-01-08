// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.27 15:49:40
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

const int N = 1e5 + 10;
int n, ans, cnt[N];

void main() {
    read(n);
    for (int i = 1, u, v; i < n; i++) read(u), read(v), ++cnt[u], ++cnt[v];
    for (int i = 1; i <= n; i++) ans = std::max(ans, cnt[i] + 1);
    print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }