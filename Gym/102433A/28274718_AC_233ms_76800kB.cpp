#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 1e6 + 5;

int n, a[N], siz[N];
long long sum[N], p[N], q[N], ans[N];
std::vector<std::pair<int, int>> e[N];

void dfs1(int u, int fa) {
    siz[u] = 1; sum[u] = a[u];
    for (auto i : e[u]) {
        int v = i.first, w = i.second;
        if (v == fa) { continue; }
        dfs1(v, u);
        siz[u] += siz[v];
        sum[u] += sum[v];
    }
}
void dfs2(int u, int fa) {
    for (auto i : e[u]) {
        int v = i.first, w = i.second;
        if (v == fa) { continue; }
        p[v] += (siz[1] - siz[v]) * w;
        q[v] += (sum[1] - sum[v]) * w;
        dfs2(v, u);
        p[1] += siz[v] * w;
        q[1] += sum[v] * w;
        p[v] -= siz[v] * w;
        q[v] -= sum[v] * w;
    }
}
void dfs3(int u, int fa, long long x, long long y) {
    x += p[u]; y += q[u];
    ans[u] += x * a[u] + y;
    for (auto i : e[u]) {
        int v = i.first, w = i.second;
        if (v == fa) { continue; }
        dfs3(v, u, x, y);
    }
}

int main() {
    n = read();
    for (int u = 1; u <= n; u++) { a[u] = read(); }
    for (int i = 1; i < n; i++) {
        int u = read(), v = read(), w = read();
        e[u].push_back({v, w});
        e[v].push_back({u, w});
    }
    dfs1(1, 0); dfs2(1, 0); dfs3(1, 0, 0, 0);
    for (int u = 1; u <= n; u++) { printf("%lld\n", ans[u]); }
    return 0;
}