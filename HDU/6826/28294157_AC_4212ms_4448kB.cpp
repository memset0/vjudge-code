#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)

using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') { fu = -1; } c = getchar(); }
    while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 1e5 + 5;

ll t;
int cat[N], a[N], s[N], s1[N], s2[N];
int T, n, m, q;

inline int add(int x, int y) {
    x += y;
    if (x >= n) x -= n;
    return x;
}

inline int sub(int x, int y) {
    x -= y;
    if (x < 0) x += n;
    return x;
}

inline int mul(int x, int y) { return 1ll * x * y % n; }

inline int fpow(int x, ll y) {
    int ans = 1;
    while (y) {
        if (y & 1) ans = mul(ans, x);
        y >>= 1; x = mul(x, x);
    }
    return ans;
}

struct fenwick {
    int f[N];

    inline int lowbit(int x) { return x & -x; }

    inline void add(int x, int y) {
        while (x <= n) {
            f[x] = ::add(f[x], y);
            x += lowbit(x);
        }
    }

    inline int query(int x) {
        int ans = 0;
        while (x) {
            ans = ::add(ans, f[x]);
            x ^= lowbit(x);
        }
        return ans;
    }
} tr1, tr2, tr3, tr4;

inline int gets(int l, int r) {
    if (l > r) return 0;
    if (l <= n && r <= n) return sub(s[r], s[l - 1]);
    if (l <= n && r > n) return add(s[r - n], sub(s[n], s[l - 1]));
    return gets(l - n, r - n);
}

inline int calcs1(int l, int r) { return sub(sub(s1[r], s1[l - 1]), mul(gets(l, r), l - 1)); }

inline int gets1(int l, int r) {
    if (l > r) return 0;
    if (l <= n && r <= n) return calcs1(l, r);
    if (l <= n && r > n) return add(add(calcs1(l, n), calcs1(1, r - n)), mul(gets(1, r - n), n - l + 1));
    return gets1(l - n, r - n);
}

inline int calcs2(int l, int r) { return sub(sub(s2[r], s2[l - 1]), mul(gets(l, r), n - r)); }

inline int gets2(int l, int r) {
    if (l > r) return 0;
    if (l <= n && r <= n) return calcs2(l, r);
    if (l <= n && r > n) return add(add(calcs2(l, n), calcs2(1, r - n)), mul(gets(l, n), r - n));
    return gets2(l - n, r - n);
}

inline int getsum(int x) { return 1ll * x * (x - 1) / 2 % n; }

int main() {
    read(T);
    while (T--) {
        read(n); read(t); read(m); read(q);
        for (int i = 1; i <= n; i++) tr1.f[i] = tr2.f[i] = tr3.f[i] = tr4.f[i] = 0;
        int now = 0, sum = 0;
        // for (int i = 1; i <= n; i++) read(cat[i]), sum += cat[i];
        // for (int i = 2; i <= n; i++) now += cat[n + 2 - i] * (i - 1);
        // a[1] = now;
        // for (int i = 2; i <= n; i++) now += sum, now -= cat[i] * n, a[i] = now;
        // for (int i = 1; i <= n; i++) cout << a[i] << " ";
        // cout << endl;
        for (int i = 1; i <= n; i++) read(cat[i]), sum = add(sum, cat[i]);
        for (int i = 2; i <= n; i++) now = add(now, mul(cat[n + 2 - i], i - 1));
        a[1] = now;
        for (int i = 2; i <= n; i++) now = add(now, sum), now = sub(now, mul(cat[i], n)), a[i] = now;
        for (int i = 1; i <= n; i++) s[i] = add(s[i - 1], fpow(a[i], t)), s1[i] = add(s1[i - 1], mul(i, fpow(a[i], t))), s2[i] = add(s2[i - 1], mul(n - i + 1, fpow(a[i], t)));
        for (int i = 1; i <= m; i++) {
            int opt, xl, yl, xr, yr, l, r, ans = 0;
            read(opt); read(xl); read(yl); read(xr); read(yr); ++xl; ++yl; ++xr; ++yr;
            l = yl - xr + 1 + n; r = yr - xr + 1 + n;
            if (xr - xl <= yr - yl) {
                ans = mul(gets(l + xr - xl, r), xr - xl + 1);
                ans = add(ans, gets1(l, l + xr - xl - 1));
                ans = add(ans, gets2(r + 1, r + xr - xl));
            } else {
                ans = mul(gets(r, l + xr - xl), yr - yl + 1);
                ans = add(ans, gets1(l, r - 1));
                ans = add(ans, gets2(l + xr - xl + 1, r + xr - xl));
            }
            print(ans, '\n');
        }
        for (int i = 1; i <= n; i++) s[i] = add(s[i - 1], a[i]), s1[i] = add(s1[i - 1], mul(i, a[i])), s2[i] = add(s2[i - 1], mul(n - i + 1, a[i]));
        for (int i = 1; i <= q; i++) {
            int opt; read(opt);
            if (opt == 1) {
                int x, k, v;
                read(x); read(k); read(v); ++x;
                tr1.add(x, k); tr2.add(x, mul(k, n - v));
            }
            if (opt == 2) {
                int y, k, v;
                read(y); read(k); read(v); ++y;
                tr3.add(y, k); tr4.add(y, mul(k, n - v));
            }
            if (opt == 3) {
                int xl, yl, xr, yr, l, r, ans = 0;
                read(xl); read(yl); read(xr); read(yr); ++xl; ++yl; ++xr; ++yr;
                l = yl - xr + 1 + n; r = yr - xr + 1 + n;
                if (xr - xl <= yr - yl) {
                    ans = mul(gets(l + xr - xl, r), xr - xl + 1);
                    ans = add(ans, gets1(l, l + xr - xl - 1));
                    ans = add(ans, gets2(r + 1, r + xr - xl));
                } else {
                    ans = mul(gets(r, l + xr - xl), yr - yl + 1);
                    ans = add(ans, gets1(l, r - 1));
                    ans = add(ans, gets2(l + xr - xl + 1, r + xr - xl));
                }
                ans = add(ans, mul(sub(getsum(yr), getsum(yl - 1)), sub(tr1.query(xr), tr1.query(xl - 1))));
                ans = add(ans, mul(yr - yl + 1, sub(tr2.query(xr), tr2.query(xl - 1))));
                ans = add(ans, mul(sub(getsum(xr), getsum(xl - 1)), sub(tr3.query(yr), tr3.query(yl - 1))));
                ans = add(ans, mul(xr - xl + 1, sub(tr4.query(yr), tr4.query(yl - 1))));
                print(ans, '\n');
            }
        }
    }
    return 0;
}