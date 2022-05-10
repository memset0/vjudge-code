// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.17 12:30:31
//   website: https://memset0.cn/
// ===========	=====================
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

const int N = 2e5 + 10, L = 11;
int n, m, C1, C2;
int fa[N], rev[N], ch[N][2], fac[L];

struct poly {
	double f[L];
	int op_t; double a_t, b_t;
	inline void init(int op, double a, double b) {
		memset(f, 0, sizeof(f));
		if (op == 1) {
			double flag = 1, sin_t = sin(b), cos_t = cos(b);
			for (int i = 0; i < L; i++) {
				f[i] = flag * (i & 1 ? cos_t : sin_t) / fac[i];
				flag *= a; if (i & 1) flag *= -1;
			}
		} else if (op == 2) {
			double flag = 1, exp_t = exp(b);
			for (int i = 0; i < L; i++) f[i] = flag * exp_t / fac[i], flag *= a;
		} else if (op == 3) f[0] = b, f[1] = a;
		op_t = op, a_t = a, b_t = b;
	}
	inline double calc(double x) {
		double ans = 0, mul = 1;
		for (int i = 0; i < L; i++) ans += f[i] * mul, mul *= x;
		return ans;
	}
	inline double calc_t(double x) {
		if (op_t == 1) return sin(a_t * x + b_t);
		else if (op_t == 2) return exp(a_t * x + b_t);
		else return a_t * x + b_t;
	}
	friend inline poly operator + (const poly &a, const poly &b) {
		static poly c;
		for (int i = 0; i < L; i++) c.f[i] = a.f[i] + b.f[i];
		return c;
	}
	inline void print() { for (int i = 0; i < L; i++) printf("%.2lf%c", f[i], " \n"[i == L - 1]); }
} val[N], sum[N];

inline bool getSon(int u) { return ch[fa[u]][1] == u; }
inline bool isRoot(int u) { return ch[fa[u]][0] != u && ch[fa[u]][1] != u; }
inline void update(int u) { sum[u] = sum[ch[u][0]] + sum[ch[u][1]] + val[u]; }
inline void cleanUp(int u) {
	if (!isRoot(u)) cleanUp(fa[u]);
	if (rev[u]) std::swap(ch[u][0], ch[u][1]), rev[ch[u][0]] ^= 1, rev[ch[u][1]] ^= 1, rev[u] = 0;
}
inline void rotate(int x) {
	if (!x || !fa[x]) return;
	int f = fa[x], fs = getSon(x), ff = fa[f], ffs = getSon(f), y = ch[x][fs ^ 1];
	if (!isRoot(f)) ch[ff][ffs] = x; ch[f][fs] = y, ch[x][fs ^ 1] = f;
	fa[y] = f, fa[f] = x, fa[x] = ff, update(f), update(x);
}
inline void splay(int u) {
	cleanUp(u);
	for (int f = fa[u]; !isRoot(u); rotate(u), f = fa[u])
		if (!isRoot(f)) rotate(getSon(f) == getSon(u) ? f : u);
	update(u);
}
inline void access(int x) { for (int y = 0; x; y = x, x = fa[x]) splay(x), ch[x][1] = y, update(x); }
inline void makeRoot(int x) { access(x), splay(x), rev[x] ^= 1; }
inline int getRoot(int x) { access(x), splay(x); while (ch[x][0]) x = ch[x][0]; return x; }
inline void split(int x, int y) { makeRoot(x), access(y), splay(y); }
inline void link(int x, int y) { makeRoot(x), fa[x] = y, update(y); }
inline void cut(int x, int y) { split(x, y), ch[y][0] = fa[x] = 0, update(y); }

void main() {
	fac[0] = 1;
	for (int i = 1; i < L; i++) fac[i] = fac[i - 1] * i;
	read(n), read(m), C1 = getchar(), C2 = getchar();
	for (int i = 1, f; i <= n; i++) { double a, b;
		read(f), scanf("%lf%lf", &a, &b);
		val[i].init(f, a, b);
		// for (double x = 0; x <= 1; x += 0.1)
		// 	printf(">>> [%.1lf] %lf %lf\n", x, val[i].calc(x), val[i].calc_t(x));
	}
	for (int i = 1, op, c, f, u, v; i <= m; i++) { double a, b, x;
		while (op = getchar(), !islower(op));
		if (op == 'a') read(u), read(v), link(++u, ++v);
		else if (op == 'd') read(u), read(v), cut(++u, ++v);
		else if (op == 'm') {
			read(c), read(f), scanf("%lf%lf", &a, &b);
			makeRoot(++c), val[c].init(f, a, b), update(c);
		} else {
			read(u), read(v), scanf("%lf", &x);
			if (getRoot(++u) == getRoot(++v)) {
				split(u, v), printf("%.10lf\n", sum[v].calc(x));
			} else puts("unreachable");
		}
	}
}

} signed main() { return ringo::main(), 0; }