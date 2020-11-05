// luogu-judger-enable-o2
// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

template <typename T> inline void read(T &x) {
    x = 0; register char ch; register bool fl = 0;
    while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
    while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
    if (fl) x = -x;
}
template <typename T> inline void readc(T &x) {
    while (x = getc(), !islower(x) && !isupper(x));
}
template <typename T> inline void print(T x, char c = ' ') {
    static int buf[40];
    if (x == 0) { putc('0'); putc(c); return; }
    if (x < 0) putc('-'), x = -x;
    for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
    while (buf[0]) putc((char) buf[buf[0]--]);
    putc(c);
}

const int maxn = 37, maxm = 2500, maxe = 10010, inf = 1000000010;
int n, m, u, p, s, e, l, r;
int flow, cost, max_flow, max_cost;
int w[maxn][maxn], al[maxn][maxn], ar[maxn][maxn];
int q[maxm], inq[maxm], pre[maxm], dis[maxm];
int tot = 2, hed[maxm], nxt[maxe], to[maxe], val[maxe], cst[maxe], tag[maxe];
int findWay, nowRobot;
std::vector < int > nowWay;

inline void add_edge(int u, int v, int w, int c, int t) {
//	printf("add edge %d %d %d %d %d\n", u, v, w, c, t);
    nxt[tot] = hed[u], to[tot] = v, val[tot] = w, cst[tot] =  c, tag[tot] =  t, hed[u] = tot++;
    nxt[tot] = hed[v], to[tot] = u, val[tot] = 0, cst[tot] = -c, tag[tot] = -1, hed[v] = tot++;
}

bool spfa() {
    memset(pre, 0, sizeof(pre));
    memset(dis, -63, sizeof(dis));
    l = r = 1, q[1] = s, inq[s] = 1, dis[s] = 0;
    while (l <= r) {
        u = q[(l++) % e], inq[u] = 0;
        for (int i = hed[u], v = to[i]; i; i = nxt[i], v = to[i])
            if (val[i] && dis[u] + cst[i] > dis[v]) {
                dis[v] = dis[u] + cst[i];
                pre[v] = i;
                if (!inq[v]) {
                    inq[v] = 1;
                    q[(++r) % e] = v;
                }
            }
    }
    return pre[e];
}

void dfs(int u) {
//	if (nowRobot == 2)
//		printf("dfs %d\n", u);
    if (u == e) {
        findWay = true;
        for (std::vector < int > ::iterator it = nowWay.begin(); it != nowWay.end(); it++)
            if (~tag[*it]) {
                print(nowRobot);
                print(tag[*it], '\n');
                val[(*it) ^ 1] -= 1;
            }
        return;
    }
    for (int i = hed[u]; i && !findWay; i = nxt[i])
        if (val[i ^ 1] && (!(i & 1))) {
            val[i ^ 1] -= 1;
            nowWay.push_back(i);
            dfs(to[i]);
            nowWay.pop_back();
            val[i ^ 1] += 1;
        }
}

int main() {
//	freopen("INPUT", "r", stdin);

    read(p), read(m), read(n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            read(w[i][j]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            al[i][j] = (i - 1) * m + j;
            ar[i][j] = al[i][j] + n * m;
        }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (i ^ n) add_edge(ar[i][j], al[i + 1][j], inf, 0, 0);
            if (j ^ m) add_edge(ar[i][j], al[i][j + 1], inf, 0, 1);
            switch (w[i][j]) {
                case 0:
                    add_edge(al[i][j], ar[i][j], inf, 0, -1);
                    break;
                case 1:
                    break;
                case 2:
                    add_edge(al[i][j], ar[i][j], inf, 0, -1);
                    add_edge(al[i][j], ar[i][j], 1, 1, -1);
                    break;
            }
        }
    s = n * m * 2 + 1, e = s + 1;
    add_edge(s, al[1][1], p, 0, -1);
    add_edge(ar[n][m], e, p, 0, -1);

//	printf("ready to spfa\n");
    while (spfa()) {
        flow = inf, cost = 0;
        for (int i = pre[e]; i; i = pre[to[i ^ 1]])
            flow = std::min(flow, val[i]);
        for (int i = pre[e]; i; i = pre[to[i ^ 1]]) {
            val[i] -= flow, val[i ^ 1] += flow;
            cost += cst[i] * flow;
        }
        max_flow += flow, max_cost += cost;
//		printf("find a new way %d %d\n", flow, cost);
    }
//	printf(">>> %d %d\n", max_flow, max_cost);
    for (int k = 1; k <= max_flow; k++) {
        nowRobot = k;
        findWay = false;
        dfs(s);
    }
    
    return 0;
}
