#include <bits/stdc++.h>
#ifndef popteam
#define endl '\n'
#endif
#define all(x) begin(x), end(x)
using namespace std;

const int N = 3e5;
int n, m, u, v, w, vis[N + 10];
int dfn[N + 10], low[N + 10], nw, q[N + 10], iq[N + 10], sz;
int cnt, fr[N + 10];
vector<int> e1[N + 10], e2[N + 10];
void dfs(int x) {
    vis[x] = 1;
    for (int i : e1[x])
        if (!vis[i]) dfs(i);
}
void Tarjan(int x) {
    dfn[x] = low[x] = ++nw;
    iq[x] = 1, q[++sz] = x;
    for (int i : e2[x]) {
        if (!dfn[i])
            Tarjan(i), low[x] = min(low[x], low[i]);
        else if (iq[i])
            low[x] = min(low[x], dfn[i]);
    }
    if (low[x] == dfn[x]) {
        ++cnt;
        while (q[sz] != x)
            fr[q[sz]] = cnt, iq[q[sz--]] = 0;
        fr[q[sz]] = cnt, iq[q[sz--]] = 0;
    }
}
int main() {
#ifdef popteam
    freopen("I.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> u >> v >> w;
        if (w == 2) e2[u].push_back(v);
        e1[u].push_back(v);
    }
    dfs(1);
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) Tarjan(i);
    for (int i = 1; i <= n; ++i)
        if (vis[i]) {
            for (int j : e2[i])
                if (fr[i] != fr[j]) {
                    cout << "Yes\n";
                    return 0;
                }
        }
    cout << "No\n";
}