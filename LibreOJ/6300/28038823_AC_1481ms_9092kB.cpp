// =================================
//   author: memset0
//   date: 2019.06.18 10:19:18
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

const int N = 3e5 + 10, mod = 1e9 + 7;
int t, p, max, now, sqn, n[N], m[N], fac[N], ifac[N], ans[N], bln[N];

struct query {
	int l, r, id;
	inline bool operator<(const query &other) const {
		return bln[l] == bln[other.l] ? r < other.r : l < other.l;
	}
};
std::vector<query> q;

inline int half(int x) { return x & 1 ? (x + mod) >> 1 : x >> 1; }
inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }
inline int c(int n, int m) { return n < m ? 0 : mul(fac[n], mul(ifac[m], ifac[n - m])); }

void main() {
	read(t), read(p);
	for (int i = 1, n, m; i <= t; i++) {
		read(n), read(m), max = std::max(max, n + m);
		if (n && m) q.push_back({std::min(n, m) - 1, n + m, i});
		ringo::n[i] = n, ringo::m[i] = m;
	}
	sqn = sqrt(max);
	for (int i = 0; i <= max; i++) bln[i] = i / sqn;
	fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
	for (int i = 2; i <= max; i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= max; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= max; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	std::sort(q.begin(), q.end());
	int l = q.begin()->l, r = q.begin()->r;
	for (int i = 0; i <= l; i++) now = inc(now, c(r, i));
	ans[q.begin()->id] = now;
	for (auto it = std::next(q.begin()); it != q.end(); it++) {
		while (l > it->l) now = dec(now, c(r, l--));
		while (r < it->r) now = dec(inc(now, now), c(r++, l));
		while (l < it->l) now = inc(now, c(r, ++l));
		while (r > it->r) now = half(inc(now, c(--r, l)));
		// printf(">> %d %d : %d\n", it->l, it->r, now);
		ans[it->id] = now;
	}
	for (int i = 1; i <= t; i++) ans[i] = mul(ans[i], inv(c(n[i] + m[i], n[i])));
	// for (int i = 1; i <= t; i++) print(ans[i], " \n"[i == t]);
	for (int i = 1; i <= t; i++)
		print(n[i] < m[i] ? ans[i] : inc(ans[i], n[i] - m[i]), '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}
