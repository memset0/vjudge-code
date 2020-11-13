// =================================
//   author: memset0
//   date: 2019.07.30 19:45:56
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
#define rep(i, l, r) for (int i = (l), i##ed = (r); i <= i##ed; ++i)
#define for_each(i, a) for (size_t i = 0, i##ed = a.size(); i < i##ed; ++i)
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

const int N = 650000, L = 40, mod = 1e12 + 39;
int n, sqn, nod, cnt, sum, ans, a[N], f[N], g[N], h[N], s[N], pri[N];

inline int id(int x) { return x <= sqn ? x : nod - n / x + 1; }
inline int dec(int a, int b, int mod) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b, int mod) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b, int mod) { return (a * b - (int)((long double)a * b / mod) * mod) % mod; }
inline int fpow(int a, int b, int mod) { int s = 1; for (; b; b >>= 1, a = mul(a, a, mod)) if (b & 1) s = mul(s, a, mod); return s; }
inline int calc(int x) { return x & 1 ? mul((x + 1) >> 1, x, mod - 1) : mul(x >> 1, x + 1, mod - 1); }

int solve(int n) {
	// std::cerr << "solve(" << n << ")" << std::endl;
	sqn = sqrt(n), ans = 1, nod = cnt = sum = 0;
	for (int i = 1; i <= n; i = a[nod] + 1) {
		a[++nod] = n / (n / i);
		g[nod] = calc(a[nod]) - 1;
		h[nod] = a[nod] - 1;
	}
	for (int i = 2; i <= sqn; i++) if (h[i] != h[i - 1]) {
		pri[++cnt] = i;
		// printf(">>> %lld %lld\n", i, h[i]);
		for (int j = nod; i * i <= a[j]; j--) {
			// printf("> %lld %lld : %lld %lld : %lld\n", i, j, h[id(a[j] / i)], h[j - 1], mul(i, dec(g[id(a[j] / i)], g[j - 1], mod - 1), mod - 1));
			h[j] = dec(h[j], dec(h[id(a[j] / i)], h[i - 1], mod - 1), mod - 1);
			g[j] = dec(g[j], mul(i, dec(g[id(a[j] / i)], g[i - 1], mod - 1), mod - 1), mod - 1);
		}
	}
	// print(a, 1, nod, "a"), print(g, 1, nod, "g"), print(h, 1, nod, "h");
	static int t[L]; memset(t, 0, sizeof(t));
	for (int i = 1; i <= cnt && pri[i] <= sqn; i++)
		for (int j = 1, x = pri[i], y = pri[i] * pri[i]; x <= n; j++, x = y, y *= pri[i]) {
			t[j] = inc(t[j], dec(mul(calc(n / x), x, mod - 1), mul(calc(n / y), y, mod - 1), mod - 1), mod - 1);
		}
	for (int i = 1; i < L; i++) ans = mul(ans, fpow(i + 1, t[i], mod), mod);
	for (int i = 1; i <= sqn; i++) sum = inc(sum, mul(calc(a[i]), dec(g[nod - i + 1], g[std::max(sqn, nod - i)], mod - 1), mod - 1), mod - 1);
	ans = mul(ans, fpow(2, sum, mod), mod);
	// printf(">> %lld\n", ans);
	for (int i = 1; i <= nod; i++) s[i] = f[i] = dec(0, h[i], mod - 1);
	for (int i = cnt; i; i--)
		for (int j = nod; pri[i] * pri[i] <= a[j]; j--) {
			f[j] = dec(f[j], inc(f[id(a[j] / pri[i])], i, mod - 1), mod - 1);
			s[j] = dec(s[j], inc(inc(s[id(a[j] / pri[i])], f[id(a[j] / pri[i])], mod - 1), inc(i, i, mod - 1), mod - 1), mod - 1);
		}
	// print(s, 1, nod, "s"), print(f, 1, nod, "f");
	ans = mul(ans, fpow(2, s[id(n)], mod), mod);
	return ans;
}

void main() { int T; read(T); while (T--) read(n), print(solve(n), '\n'); }

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	return ringo::main(), 0;
}