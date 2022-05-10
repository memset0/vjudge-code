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
        for (int r = 0; r <= n; r++) {
            C.reset();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) C.a[i][j] = dec(0, A[1].a[i][j]);
                add(C.a[i][i], r);
            }
            y[r] = C.det();
        }
        lagrange(y, p);
        M[0] = A;
        for (int i = 2; i < n; i++) M[1].a[i][i] = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) add(V[i], M[i].a[j][j]);
        }
        memset(P, 0, sizeof P), P[0] = 1;
        for (int d, i = 1; i <= l; i++) {
            for (int i = n; i; i--) add(P[i], P[i - 1]);
            d = (ll)P[n] * finv(p[n]);
            for (int i = 0; i <= n; i++) sub(P[i], (ll)p[i] * d % mod);
            for (int i = 0; i < n; i++) inc(DP[k][i], (ll)V[i] * P[i] % mod);
        }
        d = finv((ll)fpow(m, i) * n % mod) % mod;
        for (int i = 1; i <= l; i++) DP[k][i] = (ll)DP[k][i] * d % mod;
    }

    for (int x = 0; x < n; x++) {
        memset(P, 0, lim << 2), P[0] = 1;
        memset(F, 0, (m + 1) << 2), memset(V, 0, n << 2);
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if ((i & x) == x && (j & x) == x) {
                        add(V[k], A[k].a[i][j]);
                    }
        }
        // printf("V: "), print(V, 0, n - 1);
        for (int k = 1; k <= m; k++) {
            for (int i = n; i; i--) P[i] = P[i - 1];
            P[0] = 0; ll d = P[n] * finv(p[n]) % mod;
            for (int i = 0; i <= n; i++) sub(P[i], d * p[i] % mod);
            for (int i = 0; i < n; i++) sub(F[k], (ll)P[i] * V[i] % mod);
            // printf("P[%d]: ", k), print(P, 0, n);
        }
        F[0] = 1, polyinv(F, G, lim);
        // printf(">>> %d\n", x), print(F, 1, m), print(G, 1, m), puts("");
        for (int k = 1; k <= m; k++)
            for (int y = 0; y < n; y++) 
                if ((x & y) == y) {
                    if ((__builtin_popcount(x) ^ __builtin_popcount(y)) & 1)
                        sub(ans[y][k], G[k]);
                    else
                        add(ans[y][k], G[k]);
                }
    }
    // for (int i = 0; i < n; i++) print(ans[i], 1, m);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= m; j++) out ^= ans[i][j];
    }
    print(out, '\n');
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	ringo::main();
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
}
