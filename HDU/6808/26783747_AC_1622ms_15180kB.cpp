#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') { fu = -1; } c = getchar(); }
    while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int INF = 0x7fffffff;

struct max_flow_t {
    struct edge_t {
        int u, v, next, cap, flow;
        edge_t () {}
        edge_t (int a, int b, int c, int d, int e) : u(a), v(b), next(c), cap(d), flow(e) {}
    };

    vector <edge_t> G;
    vector <int> head, nowhead, d;
    int n, s, t, tot;

    max_flow_t () { G.clear(); head.clear(); tot = 1; }
    max_flow_t (int nn) {
        n = nn; s = 0; t = n + 1;
        G.clear(); head.clear(); head.resize(n + 2, 0); tot = 1;
    }

    inline void addedge(int u, int v, int cap) {
        G.resize(tot + 3);
        G[++tot] = (edge_t) {u, v, head[u], cap, 0}, head[u] = tot;
        G[++tot] = (edge_t) {v, u, head[v], 0, 0}, head[v] = tot;
    }

    int bfs() {
        d.clear(); d.resize(n + 2, 0); d[s] = 1;
        queue <int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; i; i = G[i].next) {
                int v = G[i].v;
                if (G[i].cap > G[i].flow && d[v] == 0) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[t];
    }

    int dfs(int u, int Flow) {
        if (u == t || !Flow) return Flow;
        int flow = 0, f;
        for (int &i = nowhead[u]; i; i = G[i].next) {
            int v = G[i].v;
            if (d[v] == d[u] + 1 && (f = dfs(v, min(Flow, G[i].cap - G[i].flow))) > 0) {
                G[i].flow += f; G[i ^ 1].flow -= f;
                flow += f; Flow -= f;
                if (!Flow) break;
            }
        }
        return flow;
    }

    int dinic() {
        int ans = 0;
        while (bfs()) {
            nowhead = head;
            ans += dfs(s, INF);
        }
        return ans;
    }
} M;

const int N = 1e5 + 5;

int a[N], b[N], x[N], t[N];
int T, n, al, bl;

int main() {
    read(T);
    while (T--) {
        read(n);
        for (int i = 1; i <= n; i++) {
            read(x[i]); read(t[i]);
            a[i] = x[i] - t[i]; b[i] = x[i] + t[i];
        }
        sort(a + 1, a + n + 1); al = unique(a + 1, a + n + 1) - a - 1;
        sort(b + 1, b + n + 1); bl = unique(b + 1, b + n + 1) - b - 1;
        M = max_flow_t(al + bl);
        for (int i = 1; i <= n; i++) {
            int u = lower_bound(a + 1, a + al + 1, x[i] - t[i]) - a;
            int v = lower_bound(b + 1, b + bl + 1, x[i] + t[i]) - b;
            M.addedge(u, v + al, 1);
        }
        for (int i = 1; i <= al; i++) M.addedge(M.s, i, 1);
        for (int i = 1; i <= bl; i++) M.addedge(i + al, M.t, 1);
        print(M.dinic(), '\n');
    }
    return 0;
} // 1231312312