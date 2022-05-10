// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.11 15:52:02
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

const int N = 70;
int n, m, p, ans, a[N], cnt[N], fac[N], ifac[N];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + p : a; }
inline int inc(int a, int b) { a += b; return a >= p ? a - p : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / p * p; }
inline int inv(int x) { return x < 2 ? 1 : (ll)(p - p / x) * inv(p % x) % p; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

inline int solve(int k) {
	// printf("solve %d\n", k);
	int cost = 1, kind = fac[n];
	// for (int i = 1; i <= k; i++) print(a[i], " \n"[i == k]);
    for (int i = 1; i <= k; i++) cost = mul(cost, fpow(m, a[i] >> 1));
	for (int i = 1; i <= k; i++)		
		for (int j = i + 1; j <= k; j++)
			cost = mul(cost, fpow(m, std::__gcd(a[i], a[j])));
	// printf(">> cost = %d\n", cost);
	for (int i = 1; i <= k; i++) kind = mul(kind, inv(a[i]));
	for (int i = 1; i <= k; i++) cnt[a[i]]++;
	for (int i = 1; i <= a[k]; i++) kind = mul(kind, ifac[cnt[i]]);
	for (int i = 1; i <= k; i++) cnt[a[i]]--;
	// printf(">> kind = %d\n", kind);
	return mul(cost, kind);
}

void dfs(int u, int last) {
	// printf("dfs %d %d | %d\n", u, last, a[u - 1]);
    if (!last) { ans = inc(ans, solve(u - 1)); return; }
    for (int i = a[u - 1]; i <= last; i++) a[u] = i, dfs(u + 1, last - i);
}

void main() {
	read(n), m = 2, p = 997;
	a[0] = 1, fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
	for (int i = 2; i <= n; i++) fac[i] = mul(fac[i - 1], i);
	for (int i = 2; i <= n; i++) ifac[i] = mul(p - p / i, ifac[p % i]);
	for (int i = 2; i <= n; i++) ifac[i] = mul(ifac[i - 1], ifac[i]);
	dfs(1, n), print(mul(ans, ifac[n]), '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}