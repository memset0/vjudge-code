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

const int N = 3e2 + 10, p1 = 998244353, p2 = 1e9 + 7;
int n, m;
bool a[N][N], p[N][N][N];
double p12[N], ans[N], f[N][N];

inline int dec(int a, int b, int p) { a -= b; return a < 0 ? a + p : a; }
inline int sub(int a, int b, int p) { a += b; return a >= p ? a - p : a; }
inline int mul(int a, int b, int p) { return (ll)a * b - (ll)a * b / p * p; }
inline int inv(int x, int p) { return x < 2 ? 1 : mul(p - p / x, inv(p % x, p), p); }
inline int fpow(int a, int b, int p) { int s = 1; for (; b; b >>= 1, a = mul(a, a, p)) if (b & 1) s = mul(s, a, p); return s; }

struct hash {
	int a, b;
	inline hash() {}
	inline hash(int x) { a = b = x; }
	inline hash(int x, int y) { a = x, b = y; }
	inline bool operator == (const hash &x) const { return a == x.a && b == x.b; }
	inline hash operator + (const hash &x) const { return hash(sub(a, x.a, p1), sub(b, x.b, p2)); }
	inline hash operator - (const hash &x) const { return hash(dec(a, x.a, p1), dec(b, x.b, p2)); }
	inline hash operator * (const hash &x) const { return hash(mul(a, x.a, p1), mul(b, x.b, p2)); }
} pow[N] = {hash(1)}, h[N][N];
const hash base(131, 131131);

inline hash query(int l, int r, hash *h) {
//	printf("query %d %d => %d %d %d\n", l, r, h[r].a, h[l - 1].a, pow[r - l + 1].a);
	return h[r] - h[l - 1] * pow[r - l + 1];
}

void gauss(int n, double a[N][N]) {
	for (int i = 1, j; i <= n; i++) {
//		for (int i = 1; i <= n; i++)
//			for (int j = 1; j <= n + 1; j++)
//				printf("%.2lf%c", a[i][j], " \n"[j == n + 1]);
//		puts("");
		for (j = i; j <= n; j++) if (a[j][i]) break;
		if (j > n) { puts("ERROR"), exit(0); }
		if (i != j) std::swap(a[i], a[j]);
		for (int j = i + 1; j <= n; j++) {
			double pow = a[j][i] / a[i][i];
			for (int k = i; k <= n + 1; k++) a[j][k] -= pow * a[i][k];
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = i + 1; j <= n; j++) a[i][n + 1] -= a[i][j] * ans[j];
		ans[i] = a[i][n + 1] / a[i][i];
	}
}

void main() {
	read(n), read(m);
	p12[0] = 1;
	for (int i = 1; i <= m; i++) p12[i] = p12[i - 1] * 2;
	for (int i = 1; i <= m; i++) pow[i] = pow[i - 1] * base;
	for (int i = 1, c; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			while (c = getchar(), c != 'T' && c != 'H');
			a[i][j] = c == 'H';
		}
	for (int i = 1; i <= n; i++) {
		h[i][0] = hash(1);
		for (int j = 1; j <= m; j++) h[i][j] = h[i][j - 1] * base + hash(a[i][j]);
	}
//	for (int i = 1; i <= n; i++)
//		for (int j = 0; j <= m; j++)
//			print(h[i][j].a, " \n"[j == m]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= m; k++) {
				p[i][j][k] = query(1, k, h[i]) == query(m - k + 1, m, h[j]);
//				printf("k=%d : i=%d j=%d : %d %d\n", k, i, j, query(1, k, h[i]).a, query(m - k + 1, m, h[j]).a);
			}
//	for (int k = 1; k <= m; k++) {
//		printf(">>> %d\n", k);
//		for (int i = 1; i <= n; i++)
//			for (int j = 1; j <= n; j++)
//				print(p[i][j][k], " \n"[j == n]);
//		puts("");
//	}
	f[n + 1][n + 1] = 0, f[n + 1][n + 2] = 1;
	for (int i = 1; i <= n; i++) f[n + 1][i] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= m; k++)
				f[i][j]	+= p12[k] * (double)p[i][j][k];
		f[i][n + 1] = -1, f[i][n + 2] = 0;
	}
//	for (int i = 1; i <= n + 1; i++)
//		for (int j = 1; j <= n + 2; j++)
//			printf("%.2lf%c", f[i][j], " \n"[j == n + 2]);
	gauss(n + 1, f);
	for (int i = 1; i <= n; i++) printf("%.6lf\n", ans[i]);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}
