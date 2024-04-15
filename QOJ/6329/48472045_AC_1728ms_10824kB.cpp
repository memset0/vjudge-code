#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
bool umin(auto &a, auto t) {
    if (t < a) return a = t, 1;
    return 0;
}
const int MAXN = 41011, INF = 1e9 + 233;
const ll LINF = 1.233e18;
namespace Flow {
const int N = MAXN;
struct edge {
    int v, w, cost, nxt;
} e[MAXN << 2 | 1];
int cnt = 1, last[N], cur[N];
void adde(int u, int v, int w, int c) {
    // printf("F add %d %d [%d,%d]\n", u, v, w, c);
    e[++cnt] = {v, w, c, last[u]}, last[u] = cnt;
    e[++cnt] = {u, 0, -c, last[v]}, last[v] = cnt;
}
ll dis[N];
bool vis[N], inq[N];
bool spfa(int s, int t, int n) {
    // printf("SPFA s=%d\n", s);
    for (int i = 1; i <= n; ++i)
        vis[i] = 0, dis[i] = LINF, cur[i] = last[i];
    queue<ll> q;
    dis[s] = 0;
    q.push(s);
    while (q.size()) {
        int u = q.front();
        inq[u] = 0;
        q.pop();
        for (int i = last[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if (e[i].w > 0 && umin(dis[v], dis[u] + e[i].cost))
                if (!inq[v]) q.push(v), inq[v] = 1;
        }
    }
    // printf("dis=%lld\n", dis[t]);
    return dis[t] < 0;
}
ll sumc = 0;
ll ex_flow(int u, int t, ll flow = LINF) {
    if (u == t) return flow;
    vis[u] = 1;
    ll f = 0;
    for (int &i = cur[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (e[i].w > 0 && !vis[v] && dis[v] == dis[u] + e[i].cost) {
            ll tmp = ex_flow(v, t, min((ll)e[i].w, flow - f));
            e[i].w -= tmp, e[i ^ 1].w += tmp;
            sumc += tmp * e[i].cost;
            f += tmp;
            if (f == flow) return f;
        }
    }
    return f;
}
pll min_cost_zkw(ll s, ll t, ll n) {
    ll res = 0;
    while (spfa(s, t, n))
        res += ex_flow(s, t);
    return pll(res, sumc);
}
} // namespace Flow
set<pii> S;
struct edge {
    int v, nxt;
} e[MAXN << 1 | 1];
int cnt = 1, last[MAXN];
void adde(int u, int v) { e[++cnt].v = v, e[cnt].nxt = last[u], last[u] = cnt; }

int dfn[MAXN], low[MAXN], cur = 0;
int s[MAXN], top = 0;
vector<int> seq[MAXN];
int scc[MAXN], scnt = 0;
bool ins[MAXN];
void tarjan(int u) {
    dfn[u] = low[u] = ++cur;
    s[++top] = u, ins[u] = 1;
    for (int i = last[u]; i; i = e[i].nxt) {
        int v = e[i].v;
        if (!dfn[v])
            tarjan(v), umin(low[u], low[v]);
        else if (ins[v])
            umin(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++scnt;
        while (1) {
            int x = s[top--];
            seq[scnt].emplace_back(x);
            scc[x] = scnt;
            ins[x] = 0;
            if (x == u) break;
        }
    }
}
vector<int> g[MAXN];
int color[MAXN], cc = 0;
// int n, m;
void dfs(int u) {
    // if (type) color[u] = cc;
    // printf("dfs %d\n", u);
    if (!color[seq[u][0]]) {
        for (auto x : seq[u])
            color[x] = cc;
    }
    for (int i = Flow::last[scnt + u]; i; i = Flow::e[i].nxt) {
        int v = Flow::e[i].v, w = Flow::e[i].w, &rw = Flow::e[i ^ 1].w;
        // printf("try %d %d,rw=%d\n", u, v, rw);
        if (v < u && rw) {
            --rw;
            // printf("go %d\n", v);
            dfs(v);
            return;
        }
    }
}
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        adde(u, v);
    }
    for (int u = 1; u <= n; ++u)
        if (!dfn[u]) tarjan(u);

    for (int u = 1; u <= n; ++u)
        for (int i = last[u]; i; i = e[i].nxt) {
            int v = e[i].v, p = scc[u], q = scc[v];
            if (p != q && !S.count(pii(p, q)) && !S.count(pii(q, p))) S.insert(pii(p, q)), g[p].emplace_back(q); //, printf("add %d %d\n", scc[u], scc[v]);
        }
    int S = scnt * 2 + 1, T = S + 1;
    cerr << "scnt=" << scnt << "\n";
    for (int u = 1; u <= scnt; ++u)
        for (auto v : g[u])
            Flow::adde(u + scnt, v, INF, 0);
    for (int u = 1; u <= scnt; ++u) {
        Flow::adde(S, u, INF, 1), Flow::adde(u + scnt, T, INF, 0);
        Flow::adde(u, scnt + u, 1, -INF), Flow::adde(u, scnt + u, INF, 0);
    }
    pll res = Flow::min_cost_zkw(S, T, T);
    cerr << "ans=" << res.first << '\n';
    // cout << scnt - ans << "\n";
    // for (int u = 1; u <= n; ++u)
    //     printf("scc[%d]=%d\n", u, scc[u]);
    for (int u = scnt; u; --u)
        if (!color[seq[u][0]]) {
            ++cc;
            dfs(u);
        }
    for (int u = 1; u <= n; ++u)
        cout << color[u] << " ";
    cout << '\n';
    return 0;
}