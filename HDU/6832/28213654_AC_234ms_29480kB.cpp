#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int mod = 1e9 + 7;

const int N = 1e6 + 5;

int n, m, ans, a[N], anc[N], cnt[N][2];
std::vector<std::pair<int, int>> e[N];

int find(int u) {
    return anc[u] == u ? u : anc[u] = find(anc[u]);
}

void dfs(int u, int fa) {
    cnt[u][0] = cnt[u][1] = 0;
    for (auto i : e[u]) {
        int v = i.first;
        if (v == fa) { continue; }
        dfs(v, u);
        cnt[u][0] += cnt[v][0];
        cnt[u][1] += cnt[v][1];
    }
    cnt[u][a[u]]++;
}
void solve(int u, int fa) {
    for (auto i : e[u]) {
        int v = i.first, w = i.second;
        if (v == fa) { continue; }
        solve(v, u);
        ans = (ans + 1ll * w * cnt[v][0] % mod * (cnt[1][1] - cnt[v][1])) % mod;
        ans = (ans + 1ll * w * cnt[v][1] % mod * (cnt[1][0] - cnt[v][0])) % mod;
    }
}

int main() {
    for (int T = read(); T; T--) {
        n = read(); m = read();
        for (int u = 1; u <= n; u++) {
            a[u] = read(); e[u].clear(); anc[u] = u;
        }
        int w = 1;
        for (int i = 0; i < m; i++) {
            int u = read(), v = read();
            w = w * 2 % mod;
            if (find(u) != find(v)) {
                anc[find(u)] = find(v);
                e[u].push_back({v, w});
                e[v].push_back({u, w});
            }
        }
        ans = 0;
        dfs(1, 0); solve(1, 0);
        printf("%d\n", ans);
    }
    return 0;
}