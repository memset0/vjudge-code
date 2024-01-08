// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.12 18:02:25
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

const int N = 16010, mod = 1004535809;
int n, m, x, g, len;
int a[N], s[N], t[N], pow[N], map[N], rev[N], pre_g[2][30];

inline void print(int *a, int m = m) {
	for (int i = 0; i < m; i++) print(a[i], " \n"[i == m - 1]);
}

int fpow(int a, int b, int mod) {
	int s = 1;
	for (; b; b >>= 1, a = (ll)a * a % mod)
		if (b & 1) s = (ll)s * a % mod;
	return s;
}

int get_g(int p) {
	static int stk[100]; int top = 0, x = p - 1;
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0) {
			stk[++top] = i;
			while (x % i == 0) x /= i;
		}
	if (x != 1) stk[++top] = x;
	// for (int i = 1; i <= top; i++) print(stk[i], " \n"[i == top]);
	for (int g = 2, flag = 1; ; g++, flag = 1) {
		for (int j = 1; j <= top && flag; j++)
			flag &= fpow(g, (p - 1) / stk[j], p) != 1;
		if (flag) return g;
	}
}

void ntt(int *a, int lim, int flag) {
	for (int i = 0; i < lim; i++) if (i < rev[i]) std::swap(a[i], a[rev[i]]);
	for (int len = 1, cnt = 1; len < lim; len <<= 1, ++cnt)
		for (int i = 0, wn = pre_g[flag][cnt]; i < lim; i += (len << 1))
			for (int j = 0, w = 1; j < len; j++, w = (ll)w * wn % mod) {
				int x = a[i + j], y = (ll)w * a[i + j+ len] % mod;
				a[i + j] = (x + y) % mod, a[i + j + len] = (x - y + mod) % mod;
			}
}

inline void maintain(int *a, int len) {
	for (int i = len - 1; i >= m - 1; i--) a[i % (m - 1)] += a[i], a[i] = 0;
}

void solve() {
	int len = 1, k = 0, inv;
	while (len <= ((m - 1) << 1)) len <<= 1, ++k;
	inv = fpow(len, mod - 2, mod);
	for (int i = 0; i < len; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
	memset(s, 0, sizeof(s)), s[0] = 1;
	while (n) {
		if (n & 1) {
			for (int i = 0; i < len; i++) t[i] = a[i];
			// printf("   "), print(s, len), printf(" * "), print(t, len);
			ntt(s, len, 0), ntt(t, len, 0);
			for (int i = 0; i < len; i++) s[i] = (ll)s[i] * t[i] % mod;
			ntt(s, len, 1);
			// printf(" = "), print(s, len);
			for (int i = 0; i < len; i++) s[i] = (ll)s[i] * inv % mod; 
			maintain(s, len);
			// printf(" > "), print(s, len);
		}
		n >>= 1;
		// printf("   "), print(a, len), printf(" * "), print(a, len);
		ntt(a, len, 0);
		for (int i = 0; i < len; i++) a[i] = (ll)a[i] * a[i] % mod;
		ntt(a, len, 1);
		for (int i = 0; i < len; i++) a[i] = (ll)a[i] * inv % mod;
		// printf(" = "), print(a, len);
		maintain(a, len);
		// printf(" > "), print(a, len);
	}
}

void main() {
	for (int i = 0; i < 30; i++) {
		pre_g[0][i] = fpow(3, (mod - 1) / (1 << i), mod);
		pre_g[1][i] = fpow(334845270, (mod - 1) / (1 << i), mod);
	}
	read(n), read(m), read(x), read(len);
	// printf(">> %d %d %d %d\n", n, m, x, len);
	for (int i = 1; i <= len; i++) read(s[i]);
	g = get_g(m), pow[0] = 1;
	// printf("the 原根 of %d is %d\n", m, g);
	for (int i = 1; i < m; i++) pow[i] = (ll)pow[i - 1] * g % m;
	for (int i = 0; i < m - 1; i++) map[pow[i]] = i;
	for (int i = 1; i <= len; i++) if (s[i]) a[map[s[i]]] = 1;
	solve(), print(s[map[x]], '\n');
}

} signed main() { return ringo::main(), 0; }