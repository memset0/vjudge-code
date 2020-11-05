#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 1e5 + 5, S = 450, B = 320;

int n, m, q, tot, num, deg[N], a[N], cnt[N], bln[N], bl[N], br[N], bn[N], id[N];
std::vector<int> e[N], eh[N], f[N], g[N];

struct Edge {
    int u, v;
} edg[N];

inline void insert(int u, int i) {
    u = id[u];
    int p = bln[i];
    if (f[u][i] == 0) {
        g[u][p]++;
    }
    f[u][i]++;
}
inline void erase(int u, int i) {
    u = id[u];
    int p = bln[i];
    f[u][i]--;
    if (f[u][i] == 0) {
        g[u][p]--;
    }
}

int main() {
    for (int T = read(); T; T--) {
        n = read(); m = read();
        for (int u = 1; u <= n; u++) {
            e[u].clear(); eh[u].clear();
            deg[u] = 0;
        }
        for (int u = 1; u <= n; u++) {
            a[u] = read();
        }
        for (int i = 0; i < m; i++) {
            int u = read(), v = read();
            deg[u]++; deg[v]++;
            edg[i] = (Edge) {u, v};
        }
        for (int i = 0; i < m; i++) {
            int u = edg[i].u, v = edg[i].v;
            if (deg[u] <= S) {
                e[u].push_back(v);
            } else {
                eh[v].push_back(u);
            }
            if (deg[v] <= S) {
                e[v].push_back(u);
            } else {
                eh[u].push_back(v);
            }
        }
        for (int i = 0; i <= n; i++) {
            bl[i] = br[i] = -1; bn[i] = 0;
        }
        for (int i = 0; i <= n; i++) {
            bln[i] = i / B;
            if (bl[bln[i]] == -1) { bl[bln[i]] = i; }
            br[bln[i]] = i;
            bn[bln[i]]++;
        }
        num = bln[n];
        for (int u = 0; u < tot; u++) {
            f[u].clear(); g[u].clear();
        }
        tot = 0;
        for (int u = 1; u <= n; u++) {
            if (deg[u] > S) {
                id[u] = tot++;
                f[id[u]].resize(n + 1);
                g[id[u]].resize(num + 1);
            }
        }
        for (int u = 1; u <= n; u++) {
            if (a[u] <= n) {
                for (auto v : eh[u]) {
                    insert(v, a[u]);
                }
            }
        }
        q = read();
        for (; q; q--) {
            int opt = read();
            if (opt == 1) {
                int u = read(), x = read();
                if (a[u] <= n) {
                    for (auto v : eh[u]) {
                        erase(v, a[u]);
                    }
                }
                a[u] = x;
                if (a[u] <= n) {
                    for (auto v : eh[u]) {
                        insert(v, a[u]);
                    }
                }
            } else {
                int u = read(), ans;
                if (deg[u] <= S) {
                    for (auto v : e[u]) {
                        if (a[v] <= n) { cnt[a[v]]++; }
                    }
                    ans = 0;
                    for (; cnt[ans] > 0; ans++);
                    for (auto v : e[u]) {
                        if (a[v] <= n) { cnt[a[v]]--; }
                    }
                } else {
                    u = id[u];
                    for (int p = 0; p <= num; p++) {
                        if (g[u][p] < bn[p]) {
                            int l = bl[p], r = br[p];
                            for (int i = l; i <= r; i++) {
                                if (f[u][i] == 0) {
                                    ans = i; break;
                                }
                            }
                            break;
                        }
                    }
                }
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}