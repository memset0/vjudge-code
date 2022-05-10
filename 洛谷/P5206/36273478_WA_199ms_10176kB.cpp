// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.08 07:22:47
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

const int N = 1e5 + 10, mod = 998244353;
int n, m, opt;

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

namespace sol1 {
int cnt, fa[N];
std::set <int> set[N];
int find(int x) {
	if (x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
int main() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1, u, v; i < n; i++) read(u), read(v), set[u].insert(v);
	for (int i = 1, u, v; i < n; i++) {
		read(u), read(v);
		if (set[u].count(v)) {
			if (find(u) != find(v)) fa[find(u)] = find(v);
		}
	}
	// for (int i = 1; i <= n; i++) print(find(i), " \n"[i == n]);
	for (int i = 1; i <= n; i++) if (i == find(i)) ++cnt;
	return fpow(m, cnt);
}
} // end namespace sol1

namespace sol2 {
int main() {

}
} // end namespace sol2

namespace sol3 {
int main() {

}
} // end namespace sol3

void main() {
	read(n), read(m), read(opt);
	if (opt == 0) print(sol1::main(), '\n');
	if (opt == 1) print(sol2::main(), '\n');
	if (opt == 2) print(sol3::main(), '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}