// luogu-judger-enable-o2
// =================================
//   author: memset0
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

const int N = 1e5 + 10, M = 55;
int T, n, m, maxN;
int tmpN[M], a[N], border[N];
std::vector <int> tmpA[M];

inline int dec(int a, int b, int p) { a -= b; return a < 0 ? a + p : a; }
inline int sub(int a, int b, int p) { a += b; return a >= p ? a - p : a; }
inline int mul(int a, int b, int p) { return (ll)a * b - (ll)a * b / p * p; }
inline int inv(int x, int p) { return x < 2 ? 1 : mul(p - p / x, inv(p % x, p), p); }
inline int fpow(int a, int b, int p) {
	int s = 1;
	for (; b; b >>= 1, a = mul(a, a, p))
		if (b & 1) s = mul(s, a, p);
	return s;
}

namespace hash {
	const int p1 = 1e9 + 7, p2 = 998244353, m1 = 131, m2 = 13131;
	struct hash {
		int a, b;
		inline hash() {}
		inline hash(int x) { a = b = x; }
		inline hash(int x, int y) { a = x, b = y; }
		inline bool operator == (const hash &other) const { return a == other.a && b == other.b; }
		inline hash operator + (const hash &other) const { return hash(sub(a, other.a, p1), sub(b, other.b, p2)); }
		inline hash operator - (const hash &other) const { return hash(dec(a, other.a, p1), dec(b, other.b, p2)); }
		inline hash operator * (const hash &other) const { return hash(mul(a, other.a, p1), mul(b, other.b, p2)); }
	} base, ibase, h[N], pow[N], ipow[N];
	inline void init(int n) {
		h[0] = pow[0] = ipow[0] = hash(1);
		base = hash(m1, m2), ibase = hash(inv(m1, p1), inv(m2, p2));
		for (int i = 1; i <= n; i++) {
			pow[i] = pow[i - 1] * base;
			ipow[i] = ipow[i - 1] * ibase;
		}
	} 
	inline void build(int n) {
		for (int i = 1; i <= n; i++) {
			h[i] = h[i - 1] * base + hash(a[i]);
		}
	}
	inline hash query(int l, int r) {
//		printf("hash::query %d %d => %d %d %d (%d) => %d %d\n", l, r, h[r].a, h[l - 1].a, pow[l - 1].a, (h[l - 1] * pow[l - 1]).a, (h[r] - h[l - 1] * pow[l - 1]).a, (h[r] - h[l - 1] * pow[l - 1]).b);
		return h[r] - h[l - 1] * pow[r - l + 1];
	}
}

void main() {
	read(m), read(T);
	for (int I = 1; I <= T; I++) {
		read(tmpN[I]);
		tmpA[I].resize(tmpN[I] + 1);
		for (int i = 1; i <= tmpN[I]; i++)
			read(tmpA[I][i]);
		maxN = std::max(maxN, tmpN[I]);
	}
	hash::init(maxN);
	for (int I = 1; I <= T; I++) {
		n = tmpN[I];
		for (int i = 1; i <= n; i++) {
			a[i] = tmpA[I][i];
		}
		hash::build(n);
//		for (int i = 1; i <= n; i++) {
//			printf("[%d %d]%c", hash::h[i].a, hash::h[i].b, " \n"[i == n]);
//		}
		for (int i = 1; i <= n; i++) {
			border[i] = hash::query(1, i) == hash::query(n - i + 1, n);
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) 
			if (border[i]) {
				ans = sub(ans, fpow(m, i, 10000), 10000);
			}
//		for (int i = 1; i <= n; i++) print(border[i], " \n"[i == n]);
		printf("%04d\n", ans);
	}
}
	
} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}
