// 被卡常

#include <bits/stdc++.h>
constexpr int N = 1e5, B = 33334;
int n, q, tot, cntq;
std::bitset<N> bit[B], res;
int a[N], v[N], ans[B], p[N], cnt[N], vis[B];
struct Query {
    int l, r, id;
} qry[3 * B];
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> q;
    for (int i = 0; i < n; ++i)
        std::cin >> a[i];
    std::copy(a, a + n, v);
    std::sort(v, v + n);
    tot = std::unique(v, v + n) - v;
    for (int i = 0; i < n; ++i) {
        a[i] = std::lower_bound(v, v + tot, a[i]) - v;
        ++cnt[a[i]];
    }
    for (int t = 0; t < q; t += B) {
        int m = std::min(B, q - t);
        cntq = 0;
        for (int i = 0; i < m; ++i) {
            int l, r;
            ans[i] = 0;
            for (int j = 0; j < 3; ++j) {
                std::cin >> l >> r;
                --l;
                qry[cntq++] = {l, r, i};
                ans[i] += r - l;
            }
            vis[i] = 0;
        }
        int b = std::max(1.0, n / std::sqrt(cntq));
        std::sort(qry, qry + cntq, [&](const Query &lhs, const Query &rhs) {
            if (lhs.l / b != rhs.l / b) {
                return lhs.l / b < rhs.l / b;
            } else {
                return (lhs.l / b) & 1 ? lhs.r < rhs.r : lhs.r > rhs.r;
            }
        });
        res = 0;
        p[0] = 0;
        for (int i = 0; i < tot - 1; ++i)
            p[i + 1] = p[i] + cnt[i];
        for (int i = 0, l = 0, r = 0; i < cntq; ++i) {
            while (l > qry[i].l)
                res.set(p[a[--l]]++);
            while (r < qry[i].r)
                res.set(p[a[r++]]++);
            while (l < qry[i].l)
                res.set(--p[a[l++]], 0);
            while (r > qry[i].r)
                res.set(--p[a[--r]], 0);
            if (vis[qry[i].id]) {
                bit[qry[i].id] &= res;
            } else {
                bit[qry[i].id] = res;
                vis[qry[i].id] = 1;
            }
        }
        for (int i = 0; i < m; ++i)
            std::cout << ans[i] - 3 * bit[i].count() << "\n";
    }
    return 0;
}

// 