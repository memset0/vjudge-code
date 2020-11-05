#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 1e5 + 5;

int n, m, ax[N], ay[N], b[N], p[N], dis[N];
long long ans, pre[N], f[N];

struct Fenwick1 {
    long long f[N];

    void clear(int u) {
        for (int i = u; i <= m; i += i & -i) {
            f[i] = 1e18;
        }
    }
    void modify(int u, long long x) {
        for (int i = u; i <= m; i += i & -i) {
            f[i] = std::min(f[i], x);
        }
    }
    long long query(int u) {
        long long res = 1e18;
        for (int i = u; i >= 1; i ^= i & -i) {
            res = std::min(res, f[i]);
        }
        return res;
    }
} tr1;

struct Fenwick2 {
    long long f[N];

    void clear(int u) {
        for (int i = u; i >= 1; i ^= i & -i) {
            f[i] = 1e18;
        }
    }
    void modify(int u, long long x) {
        for (int i = u; i >= 1; i ^= i & -i) {
            f[i] = std::min(f[i], x);
        }
    }
    long long query(int u) {
        long long res = 1e18;
        for (int i = u; i <= m; i += i & -i) {
            res = std::min(res, f[i]);
        }
        return res;
    }
} tr2;

bool compare(int i, int j) {
    return p[i] < p[j];
}

void cdq(int l, int r) {
    if (l == r) { return; }
    int mid = l + r >> 1;
    cdq(l, mid);
    std::vector<int> e(r - l + 1);
    for (int i = l; i <= mid; i++) {
        p[i] = ay[i - 1];
    }
    for (int i = mid + 1; i <= r; i++) {
        p[i] = ay[i];
    }
    for (int i = l; i <= r; i++) {
        e[i - l] = i;
    }
    std::sort(e.begin(), e.end(), compare);
    for (auto i : e) {
        if (i <= mid) {
            tr1.modify(ax[i - 1], f[i] - pre[i] - ay[i - 1] - b[ax[i - 1]]);
            tr2.modify(ax[i - 1], f[i] - pre[i] - ay[i - 1] + b[ax[i - 1]]);
        } else {
            long long res = 1e18;
            res = std::min(res, tr1.query(ax[i]) + b[ax[i]]);
            res = std::min(res, tr2.query(ax[i]) - b[ax[i]]);
            f[i] = std::min(f[i], res + pre[i - 1] + ay[i]);
        }
    }
    for (auto i : e) {
        if (i <= mid) {
            tr1.clear(ax[i - 1]);
            tr2.clear(ax[i - 1]);
        }
    }
    for (int _ = (int) e.size() - 1; _ >= 0; _--) {
        int i = e[_];
        if (i <= mid) {
            tr1.modify(ax[i - 1], f[i] - pre[i] + ay[i - 1] - b[ax[i - 1]]);
            tr2.modify(ax[i - 1], f[i] - pre[i] + ay[i - 1] + b[ax[i - 1]]);
        } else {
            long long res = 1e18;
            res = std::min(res, tr1.query(ax[i]) + b[ax[i]]);
            res = std::min(res, tr2.query(ax[i]) - b[ax[i]]);
            f[i] = std::min(f[i], res + pre[i - 1] - ay[i]);
        }
    }
    for (int _ = (int) e.size() - 1; _ >= 0; _--) {
        int i = e[_];
        if (i <= mid) {
            tr1.clear(ax[i - 1]);
            tr2.clear(ax[i - 1]);
        }
    }
    cdq(mid + 1, r);
}

int main() {
    for (int T = read(); T; T--) {
        n = read(); m = 0;
        for (int i = 1; i <= n; i++) {
            ax[i] = read(); ay[i] = read();
            // ax[i] = rand() * rand(); ay[i] = rand() * rand();
            b[++m] = ax[i];
            dis[i] = std::abs(ax[i] - ax[i - 1]) + std::abs(ay[i] - ay[i - 1]);
        }
        if (n <= 2) { printf("0\n"); continue; }
        pre[0] = 0;
        for (int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + dis[i];
        }
        ans = pre[n] - pre[1];
        for (int i = 2; i <= n; i++) {
            f[i] = pre[i - 1] - pre[1];
        }
        std::sort(b + 1, b + m + 1);
        m = std::unique(b + 1, b + m + 1) - b - 1;
        for (int i = 1; i <= n; i++) {
            ax[i] = std::lower_bound(b + 1, b + m + 1, ax[i]) - b;
        }
        for (int i = 1; i <= m; i++) {
            tr1.clear(i);
            tr2.clear(i);
        }
        cdq(2, n);
        for (int i = 2; i <= n; i++) {
            ans = std::min(ans, f[i] + pre[n] - pre[i]);
        }
        printf("%lld\n", ans);
    }
    return 0;
}