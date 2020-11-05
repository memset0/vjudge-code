// =================================
//   author: memset0
//   date: 2019.05.06 10:05:02
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
template <class T> inline void print(T *a, int l, int r, std::string s = "") {
    if (s != "") std::cout << s << ": ";
    for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 1e5 + 10, M = 1e2 + 10, mod = 1e7 + 19;
int n, m, t, a[M], b[M];
int ans, now, base, delta, sum_tag, mul_tag = 1, inv_mul_tag = 1;

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int inc(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }
inline int inv(int x) { return x < 2 ? 1 : mul(mod - mod / x, inv(mod % x)); }

struct mapClass {
    static const int M = 1e7 + 19, L = 1e7 + 10;
    struct pair { int key, val, nxt; } p[L];
    int top, nod, stk[L], hed[M];
    inline int hash(int x) { return x % M; }
    inline int find(int k) {
        int h = hash(k);
        for (int i = hed[h]; i; i = p[i].nxt)
            if (p[i].key == k) return p[i].val;
        return -1;
    }
    inline void set(int k, int v) {
        int h = hash(k);
        stk[top++] = h;
        p[++nod] = (pair){k, v, hed[h]}, hed[h] = nod;
    }
    inline void clear() {
        for (register int i = 0; i < top; i++)
            hed[stk[i]] = 0;
        top = nod = 0;
    }
} map;  

struct operation {
    int op, k, val, inv_val;
    inline void init() {
        read(op); 
        if (op == 1 || op == 5) read(k);
        if (op <= 4) {
            read(val), val %= mod;
            if (val < 0) val += mod;
            if (op == 3 && val) inv_val = inv(val);
        }
    }
    inline void solve() {
        // printf("solve %d %d %d\n", op, k, val);
        if (op == 1) {
            int res = map.find(k);
            if (~res) delta = inc(delta, mul(dec(val, inc(mul(res, mul_tag), sum_tag)), inv_mul_tag));
            else delta = inc(delta, mul(dec(val, inc(mul(base, mul_tag), sum_tag)), inv_mul_tag));
            map.set(k, mul(dec(val, sum_tag), inv_mul_tag));
        } else if (op == 2) {
            sum_tag = inc(sum_tag, val);
        } else if (op == 3) {
            if (val) {
                sum_tag = mul(sum_tag, val);
                mul_tag = mul(mul_tag, val);
                inv_mul_tag = mul(inv_mul_tag, inv_val);
            } else {
                base = 0, map.clear();
                sum_tag = delta = 0;
                mul_tag = inv_mul_tag = 1;
            }
        } else if (op == 4) {
            base = val, map.clear();
            sum_tag = delta = 0;
            mul_tag = inv_mul_tag = 1;
        } else if (op == 5) {
            int res = map.find(k);
            if (~res) now = inc(mul(res, mul_tag), sum_tag);
            else now = inc(mul(base, mul_tag), sum_tag);
            ans = inc(ans, now);
        } else {
            now = inc(mul(inc(mul(base, n), delta), mul_tag), mul(sum_tag, n));
            ans = inc(ans, now);
        }
    }
} p[N];

void main() {
    read(n), read(m);
    for (int i = 1; i <= m; i++) p[i].init();
    read(t);
    for (int i = 1; i <= t; i++) read(a[i]), read(b[i]);
    for (int i = 1; i <= t * m; i++) {
        int J = (i - 1) % m + 1, I = (i - J) / m + 1;
        // printf(">> %d >> %d\n", i, (a[I] + J * b[I]) % m + 1);
        p[(a[I] + (ll)J * b[I]) % m + 1].solve();
    }
    print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}
