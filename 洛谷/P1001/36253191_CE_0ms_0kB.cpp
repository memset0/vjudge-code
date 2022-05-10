// =================================
//   author: memset0
//   date: 2019.08.08 08:27:06
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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
template <class T> inline void print(T a, int l, int r) { for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]); }

const int N = 52, mod = 1e9 + 7;

inline void sub(int &a, int b) { a -= b; if (a < 0) a += mod; }
inline void add(int &a, int b) { a += b; if (a >= mod) a -= mod; }

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int finv(int x) { return x < 2 ? 1 : (ll)(mod - mod / x) * finv(mod % x) % mod; }
inline int fpow(int a, int b) { int s = 1; for (; b; b >>= 1, a = (ll)a * a % mod) if (b & 1) s = (ll)s * a % mod; return s; }

struct graph {
    int n, m;
    std::vector<std::pair<int, int>> e;
} G[N];

struct matrix {
    int a[N][N];
    void reset() { memset(a, 0, sizeof(a)); }
    matrix operator*(const matrix &rhs) const {
        matrix res; res.reset();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    res.a[i][j] = (res.a[i][j] + (ll)a[i][k] * rhs.a[k][j]) % mod;
        return res;
    }
    int det() {
        int res = 1;
        for (int i = 0, j; i < n; i++) {
            for (j = i; j < n; j++) if (a[j][i]) break;
            if (j == n) return 0;
            if (i != j) res = dec(0, res), std::swap(a[i], a[j]);
            res = (ll)res * a[i][i] % mod;
            for (int d, j = i + 1; j < n; j++) {
                d = (ll)a[j][i] * finv(a[i][i]) % mod;
                for (int k = i; k < n; k++) sub(a[j][k], (ll)a[i][k] * d % mod);
            }
        }
        return res;
    }
} C, A[N];

void lagrange(int *y, int *f) {
    static int g[N];
    for (int i = 0, d; i <= n; i++) {
        memset(g, 0, (n + 1) << 2), g[0] = d = 1;
        for (int j = 0; j <= n; j++) if (i != j) {
            d = (ll)d * (i - j + mod) % mod;
            for (int k = n; k; k--)
                g[k] = dec(g[k - 1], (ll)j * g[k] % mod);
            g[0] = (ll)g[0] * (mod - j) % mod;
        }
        d = finv(d);
        for (int j = 0; j <= n; j++) add(f[j], (ll)y[i] * g[j] % mod * d % mod);
    }
}

void main() {
	read(T);
	for (int k = 1; k <= T; k++) {
        read(n), read(m), A.reset();
        for (int u, v, i = 1; i <= m; i++) {
            read(u), read(v);
            ++A[v - 1][u - 1];
        }
        // solve p(x)
        for (int r = 0; r <= n; r++) {
            C.reset();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) C.a[i][j] = dec(0, A[1].a[i][j]);
                add(C.a[i][i], r);
            }
            y[r] = C.det();
        }
        lagrange(y, p);
        // solve DP[k][1...lim]
        M[0] = A;
        for (int i = 2; i < n; i++) M[1].a[i][i] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) add(V[i], M[i].a[j][j]);
        }
        memset(P, 0, sizeof P), P[0] = 1;
        for (int d, c = 1; c <= lim; c++) {
            for (int i = n; i; i--) add(P[i], P[i - 1]);
            d = (ll)P[n] * finv(p[n]);
            for (int i = 0; i <= n; i++) sub(P[i], (ll)p[i] * d % mod);
            for (int i = 0; i < n; i++) inc(DP[k][c], (ll)V[i] * P[i] % mod);
        }
        int d = finv((ll)fpow(m, i) * n % mod) % mod;
        for (int i = 0; i <= lim; i++) DP[k][i] = (ll)DP[k][i] * d % mod;
    }
    for (int i = 0; i <= T; i++) {
        if (i < 1) for (int j = 0; j <= lim; j++) S0[0][j] = 1;
        if (i > 0) for (int j = 0; j <= lim; j++) S0[i][j] = (ll)S0[i - 1][j] * DP[i][j] % mod;
        for (int j = 0; j <= lim; j++) S1[i][j] = finv(S0[i][j]);
    }
    for (int l = 1; l <= T; l++)
        for (int r = l; r <= T; r++) {
            for (int i = 0; i <= lim; i++) F[i] = (ll)S[r][i] * S[l - 1][i] % mod;
        }
    read(q);
    for (int u, v, k, i = 1; i <= q; i++) {
        read(u), read(v), read(k);
        print(ans[u][v][k], '\n');
    }
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	ringo::main();
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
}