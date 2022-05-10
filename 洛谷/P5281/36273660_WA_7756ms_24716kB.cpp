// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.02 13:23:23
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

const int N = 2e5 + 10, inf = 1e9, mod = 998244353, half = (mod + 1) >> 1;
bool is_leaf[N];
int fa[N], dep[N];
int n, w, c, m, L, R, LL, RR;
int f[N], g[N], ans[N], sum[N];
std::vector<int> todo1[N], todo2[N];
int tot = 2, hed[N], to[N << 1], nxt[N << 1];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) s = mul(s, a); return s; }

int pre_dp(int u) {
    int res = dep[u] & 1 ? -inf : inf;
    for (int i = hed[u], v; v = to[i], i; i = nxt[i])
        if (v != fa[u]) {
            fa[v] = u, dep[v] = dep[u] + 1;
            res = dep[u] & 1 ? std::max(res, pre_dp(v)) : std::min(res, pre_dp(v));
        }
    if (res == inf || res == -inf) {
        m += is_leaf[u] = true;
        return u;
    }
    return res;
}

inline void solve(int u) {
    if (is_leaf[u]) {
        // if (u > w) {
        //     f[u] = 1, g[u] = u - c < w ? half : 0;
        // } else if (u < w) {
        //     g[u] = 1, f[u] = u + c > w ? half : 0;
        // } else if (u == w) {
        //     f[u] = g[u] = 0;
        // }
		// (dep[u] & 1) ? g[u] = dec(1, g[u]) : f[u] = dec(1, f[u]);
        return;
    }
    f[u] = g[u] = 1;
    for (int i = hed[u], v; v = to[i], i; i = nxt[i])
        if (v != fa[u]) {
            solve(v);
            f[u] = mul(f[u], f[v]), g[u] = mul(g[u], g[v]);
        }
    f[u] = dec(1, f[u]), g[u] = dec(1, g[u]);
}

void main() {
    read(n), read(L), read(R);
	LL = std::max(L - 1, 1), RR = std::max(R, n - 1);
    for (int u, v, i = 1; i < n; i++) {
        read(u), read(v);
        nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
        nxt[tot] = hed[v], to[tot] = u, hed[v] = tot++;
    }
    dep[1] = 1, w = pre_dp(1);
	// printf("w: %d\nleaves: ", w); for (int i = 1; i <= n; i++) if (is_leaf[i]) print(i, ' '); puts("");
	for (int c, u = 1; u <= n; u++) if (is_leaf[u]) {
		if (u > w) {
			c = u - w + 1;
			f[u] = 1, g[u] = 0;
			if (LL <= c && c <= RR) todo1[c].push_back(u);
			else if (c < LL) g[u] = half;
		} else if (u < w) {
			c = w - u + 1;
			g[u] = 1, f[u] = 0;
			if (LL <= c && c <= RR) todo2[c].push_back(u);
			else if (c < LL) f[u] = half;
		} else if (u == w) {
			f[u] = g[u] = 0;
		}
		// printf("u=%d f[u]=%d g[u]=%d\n", u, f[u], g[u]);
		(dep[u] & 1) ? g[u] = dec(1, g[u]) : f[u] = dec(1, f[u]);
		// printf("u=%d f[u]=%d g[u]=%d\n", u, f[u], g[u]);
	}
	// for (int i = 1; i <= n; i++) if (is_leaf[i]) print(f[i], ' '); puts("");
	// for (int i = 1; i <= n; i++) if (is_leaf[i]) print(g[i], ' '); puts("");
    for (int i = std::max(L - 1, 1); i <= std::min(R, n - 1); i++) {
        // printf("=== %d ===\n", i);
		for (auto u : todo1[i]) {
			g[u] = half;
			(dep[u] & 1) ? g[u] = dec(1, g[u]) : f[u] = dec(1, f[u]);
		}
		for (auto u : todo2[i]) {
			f[u] = half;
			(dep[u] & 1) ? g[u] = dec(1, g[u]) : f[u] = dec(1, f[u]);
		}
        c = i, solve(1);
        sum[i] = mul(dec(1, mul(dec(1, f[1]), g[1])), fpow(2, m - 1));
        // for (int i = 1; i <= n; i++) if (is_leaf[i]) print(f[i], ' '); puts("");
        // for (int i = 1; i <= n; i++) if (is_leaf[i]) print(g[i], ' '); puts("");
    }
    for (int i = L; i <= R; i++) ans[i] = dec(sum[i], sum[i - 1]);
    ans[1] = inc(sum[1], fpow(2, m - 1));
    ans[n] = dec(dec(fpow(2, m - 1), 1), sum[n - 1]);
    for (int i = L; i <= R; i++) print(ans[i], " \n"[i == R]);
    // printf("ans: "); for (int i = 1; i <= n; i++) print(ans[i], " \n"[i == n]);
    // printf("sum: "); for (int i = 1; i <= n; i++) print(sum[i], " \n"[i == n]);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
    // freopen("1.out", "w", stdout);
#endif
    return ringo::main(), 0;
}