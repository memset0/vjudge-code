// test 

#include <cstdio>
#include <algorithm>
using namespace std;
const int Maxn = 300000;
const int Maxlog = 19;
typedef long long ll;
struct Edge {
    int to;
    Edge *nxt;
};
Edge pool[Maxn * 2 + 5];
Edge *G[Maxn + 5], *ecnt;
inline void addedge(int u, int v) {
    Edge *p = ++ecnt;
    p->to = v, p->nxt = G[u];
    G[u] = p;
}
int N;
int siz[Maxn + 5];
int mxson[Maxn + 5], mx2son[Maxn + 5];
ll ans;
int s[Maxn + 1][Maxlog + 2];
int f[Maxn + 5];
inline void clear() {
    for (int i = 1; i <= N; i++) mxson[i] = mx2son[i] = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 0; j <= Maxlog; j++) s[i][j] = 0;
    for (int i = 1; i <= N; i++) G[i] = NULL;
    ecnt = &pool[0];
    ans = 0;
}
inline void modify(int u) {
    for (int i = 1; i <= Maxlog; i++) s[u][i] = s[s[u][i - 1]][i - 1];
}
void PreDFS(int u, int fa) {
    siz[u] = 1, f[u] = fa;
    for (Edge *p = G[u]; p != NULL; p = p->nxt) {
        int v = p->to;
        if (v == fa)
            continue;
        PreDFS(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[mxson[u]]) {
            mx2son[u] = mxson[u];
            mxson[u] = v;
        } else if (siz[v] > siz[mx2son[u]])
            mx2son[u] = v;
    }
    s[u][0] = mxson[u];
    modify(u);
}
inline void calc(int u) {
    int tot = siz[u], rt = u;
    for (int i = Maxlog; i >= 0; i--)
        if (tot - siz[s[u][i]] <= tot / 2)
            u = s[u][i];
    if (siz[s[u][0]] <= tot / 2)
        ans += u;
    if (u != rt && siz[u] <= tot / 2)
        ans += f[u];
}
void DFS(int u, int fa) {
    if (fa != 0)
        calc(fa), calc(u);
    int flag = 0, t1;
    if (N - siz[u] > siz[mxson[u]]) {
        t1 = mx2son[u], flag = 1;
        mx2son[u] = mxson[u], mxson[u] = fa;
    } else if (N - siz[u] > siz[mx2son[u]]) {
        t1 = mx2son[u], flag = 2;
        mx2son[u] = fa;
    }
    for (Edge *p = G[u]; p != NULL; p = p->nxt) {
        int v = p->to;
        if (v == fa)
            continue;
        siz[u] += siz[fa] - siz[v], f[u] = v;
        if (v == mxson[u])
            s[u][0] = mx2son[u];
        else
            s[u][0] = mxson[u];
        modify(u);
        DFS(v, u);
        siz[u] -= siz[fa] - siz[v], f[u] = fa;
    }
    if (flag == 1) {
        mxson[u] = mx2son[u], mx2son[u] = t1;
    } else if (flag == 2)
        mx2son[u] = t1;
    s[u][0] = mxson[u];
    modify(u);
}
int main() {
    int _;
    scanf("%d", &_);
    while (_--) {
        scanf("%d", &N);
        clear();
        for (int i = 1; i < N; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            addedge(u, v), addedge(v, u);
        }
        PreDFS(1, 0);
        DFS(1, 0);
        printf("%lld\n", ans);
    }
    return 0;
}