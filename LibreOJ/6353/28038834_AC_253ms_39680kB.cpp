// =================================
//   author: memset0
//   date: 2019.05.22 19:24:13
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

const int N = 1e6 + 10, mod = 1e9 + 7;
int n, m, ans, fac[N], ifac[N];
double s[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }

struct info {
	int n, m, val;
	double key;
	inline info() {}
	inline info(int _n, int _m) {
		n = _n, m = _m;
		key = s[n] - s[m] - s[n - m];
		val = mul(fac[n], mul(ifac[m], ifac[n - m]));
	}
	inline bool operator<(const info &other) const {
		return key < other.key;
	}
} u;
std::priority_queue<info> q;

void main() {
	read(n), read(m);
	fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= n; i++) ifac[i] = mul(mod - mod / i, ifac[mod % i]);
	for (int i = 2; i <= n; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	for (int i = 1; i <= n; i++) s[i] = s[i - 1] + log(i);
	for (int i = 1; i <= n; i++) q.push(info(i, i >> 1));
	while (m) {
		u = q.top(), q.pop();
		--m, ans = inc(ans, u.val);
		// printf(">> %d %d => %d %.2lf\n", u.n, u.m, u.val, u.key);
		if (m && u.m != u.n - u.m) --m, ans = inc(ans, u.val);
		if (u.m - 1 >= 0) q.push(info(u.n, u.m - 1));
	}
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}
