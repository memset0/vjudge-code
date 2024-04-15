#include <bits/stdc++.h>
#ifndef popteam
#define endl '\n'
#endif
#define all(x) begin(x), end(x)
#define pi pair<int, int>
#define f first
#define s second
#define clr(x) (vector<int>().swap(x))
using namespace std;
const int N = 1e5, M = 3200;
int T, n, m, u, v, ui[(M << 1) + 10], vi[(M << 1) + 10], sz;
int fl;
vector<int> e[N + 10];
vector<pi> em[M + 10];
vector<int> f[N + 10];
struct BG {
    int a, b, p1[M + 10], p2[N + 10], vis[M + 10], T, ans;
    vector<int> t[N + 10];
    void clear() {
        for (int i = 1; i <= a; ++i)
            vector<int>().swap(t[i]);
    }
    void init(int x, int y) {
        a = x, b = y;
        for (int i = 1; i <= a; ++i)
            p1[i] = 0;
        for (int i = 1; i <= b; ++i)
            p2[i] = 0;
    }
    void add(int u, int v) { t[u].push_back(v); }
    bool dfs(int x) {
        if (vis[x] == T) return 0;
        vis[x] = T;
        for (int i : t[x]) {
            if (!p2[i] || dfs(p2[i])) {
                p1[x] = i, p2[i] = x;
                return 1;
            }
        }
        return 0;
    }
    int Match() {
        ans = 0;
        for (int i = 1; i <= a; ++i) {
            ++T, ans += dfs(i);
        }
        return ans;
    }
    void Getua(int x, vector<int> &v) {
        if (vis[x] == T) return;
        vis[x] = T, v.push_back(x);
        for (int i : t[x])
            Getua(p2[i], v);
    }
} B;
void DP(int x, int fa) {
    if (fl) return;
    for (int i : e[x])
        if (i != fa) DP(i, x);
    for (int i = 1; i <= m && !fl; ++i) {
        B.clear(), B.init(em[i].size(), e[x].size());
        for (int j = 0; j < e[x].size(); ++j)
            if (e[x][j] != fa)
                for (int k = 0; k < em[i].size(); ++k)
                    if (f[e[x][j]][em[i][k].s]) B.add(k + 1, j + 1);
        if (B.Match() == B.a) return (void)(fl = 1);
        if (B.ans == B.a - 1) {
            vector<int> t;
            for (int j = 1; j <= B.a; ++j)
                if (!B.p1[j]) ++B.T, B.Getua(j, t);
            for (int j : t)
                f[x][em[i][j - 1].s ^ 1] = 1;
        }
    }
}
int main() {
#ifdef popteam
    freopen("A.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> T;
    while (T--) {
        fl = 0;
        cin >> n;
        for (int i = 1; i <= n; ++i)
            clr(e[i]);
        for (int i = 1; i < n; ++i)
            cin >> u >> v, e[u].push_back(v), e[v].push_back(u);
        cin >> m;
        sz = 0;
        for (int i = 1; i <= m; ++i)
            vector<pi>().swap(em[i]);
        for (int i = 1; i < m; ++i) {
            cin >> u >> v;
            em[u].push_back((pi){v, sz});
            ui[sz] = u, vi[sz++] = v;
            em[v].push_back((pi){u, sz});
            ui[sz] = v, vi[sz++] = u;
        }
        for (int i = 1; i <= n; ++i) {
            clr(f[i]);
            f[i].resize(sz + 5);
        }
        DP(1, 0);
        cout << (fl ? "Yes\n" : "No\n");
    }
}