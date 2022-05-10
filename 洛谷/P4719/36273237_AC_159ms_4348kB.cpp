// luogu-judger-enable-o2
// test

#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::min; using std::max;
using std::swap; using std::sort;
using std::queue;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 1e5 + 10, M = 1e5 + 10;
int n, m, V[N], f[N][2], fa[N];
int cnt, from[N], to[N << 1], nxt[N << 1];
inline void addEdge(int u, int v) {
    to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt;
}

void dfs(int u) {
    f[u][1] = V[u], f[u][0] = 0;
    for(int i = from[u]; i; i = nxt[i]) {
        int v = to[i]; if(v == fa[u]) continue; fa[v] = u, dfs(v);
        f[u][1] += f[v][0], f[u][0] += max(f[v][1], f[v][0]);
    }
}
void undo(int u, int son) {
    if(fa[u]) undo(fa[u], u);
    if(!son) f[u][1] -= V[u];
    else f[u][1] -= f[son][0], f[u][0] -= max(f[son][1], f[son][0]);
}
void redo(int u, int son) {
    if(!son) f[u][1] += V[u];
    else f[u][1] += f[son][0], f[u][0] += max(f[son][1], f[son][0]);
    if(fa[u]) redo(fa[u], u);
}

int main () {
#ifdef OFFLINE_JUDGE
    freopen("233.in", "r", stdin);
    freopen("233.out", "w", stdout);
#endif
    read(n), read(m);
    for(int i = 1; i <= n; ++i) read(V[i]);
    for(int i = 1, u, v; i < n; ++i)
        read(u), read(v), addEdge(u, v), addEdge(v, u);
    dfs(1);
    for(int i = 1, x, y; i <= m; ++i) {
        read(x), read(y), undo(x, 0), V[x] = y, redo(x, 0); 
        printf("%d\n", max(f[1][0], f[1][1]));
    }
    return 0;
}
