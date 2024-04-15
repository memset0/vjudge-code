#include "bits/stdc++.h"
using namespace std;
const int MAXN = 200011, INF = 1e9 + 233;
vector<int> g[MAXN];
int a[MAXN];
int f[MAXN][2], fa[MAXN];
void dfs(int u) {
    int son = 0;
    for (auto v : g[u])
        son += v != fa[u];
    if (!son) {
        f[u][0] = f[u][1] = 0;
        f[u][a[u] ^ 1]++;
        return;
    }
    f[u][0] = 0, f[u][1] = -INF;
    for (auto v : g[u]) {
        if (v == fa[u]) continue;
        fa[v] = u;
        dfs(v);
        int tf0 = max(f[u][0] + f[v][0], f[u][1] + f[v][1]);
        int tf1 = max(f[u][1] + f[v][0], f[u][0] + f[v][1]);
        f[u][0] = tf0, f[u][1] = tf1;
    }
    f[u][a[u] ^ 1]++;
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    dfs(1);
    cout << max(f[1][0], f[1][1]) << '\n';
    return 0;
}