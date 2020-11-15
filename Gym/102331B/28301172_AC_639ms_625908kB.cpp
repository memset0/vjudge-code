#include <bits/stdc++.h>

inline long long read() {
    char c; long long x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int mod = 998244353, inv2 = (mod + 1) / 2;

inline int add(int x, int y) {
    return x + y >= mod ? x + y - mod : x + y;
}
inline int sub(int x, int y) {
    return x - y >= 0 ? x - y : x - y + mod;
}
inline int power(int x, int y) {
    int res = 1;
    for (; y; y >>= 1, x = 1ll * x * x % mod) {
        if (y & 1) { res = 1ll * res * x % mod; }
    }
    return res;
}

const int N = 1e6 + 5, V = 5e7 + 5;

int n, m, p;
long long k, ans, a[N];
std::map<long long, int> id;
std::vector<long long> vec[N];

struct Trie {
    int rt, tot, ls[V], rs[V], f[V];

    void reset() {
        for (int u = tot; u >= 0; u--) {
            ls[u] = rs[u] = f[u] = 0;
        }
        rt = 0; tot = 0;
    }

    inline void pushUp(int u) {
        f[u] = f[ls[u]] + f[rs[u]];
    }

    void insert(int &u, long long x, int i) {
        if (u == 0) { u = ++tot; }
        if (i == -1) { f[u]++; return; }
        if (x >> i & 1) {
            insert(rs[u], x, i - 1);
        } else {
            insert(ls[u], x, i - 1);
        }
        pushUp(u);
    }

    long long query(int u, long long x, int i) {
        if (u == 0) { return 0; }
        if (i == -1) { return f[u]; }
        if (k >> i & 1) {
            if (x >> i & 1) {
                return query(ls[u], x, i - 1);
            } else {
                return query(rs[u], x, i - 1);
            }
        } else {
            if (x >> i & 1) {
                return f[ls[u]] + query(rs[u], x, i - 1);
            } else {
                return f[rs[u]] + query(ls[u], x, i - 1);
            }
        }
    }
} tr;

int solve(std::vector<long long> a) {
    int res = 0;
    tr.reset();
    for (auto x : a) { tr.insert(tr.rt, x, p); }
    for (auto x : a) { res = add(res, tr.query(tr.rt, x, p)); }
    res = 1ll * res * inv2 % mod;
    res = add(res, a.size() + 1);
    return res;
}

int main() {
    n = read(); k = read();
    if (k == 0) {
        ans = sub(power(2, n), 1);
    } else {
        for (p = 60; p >= 0; p--) {
            if (k >> p & 1) { break; }
        }
        for (int i = 0; i < n; i++) {
            long long x = read(), y = x & ((1ll << p + 1) - 1);
            x >>= p + 1;
            if (!id[x]) { id[x] = ++m; }
            vec[id[x]].push_back(y);
        }
        ans = 1;
        for (int i = 1; i <= m; i++) {
            ans = 1ll * ans * solve(vec[i]) % mod;
        }
        ans = sub(ans, 1);
    }
    printf("%lld\n", ans);
    return 0;
}