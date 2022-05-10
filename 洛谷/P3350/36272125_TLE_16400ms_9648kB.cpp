// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.24 11:31:22
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
namespace ringo {
template <class T> inline void read(T &x) {
	x = 0; register char c = getchar(); register bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (f) x = -x;
}
template <class T> inline void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar('0' + x % 10);
}
template <class T> inline void print(T x, char c) { print(x), putchar(c); }

const int N = 1e5 + 10, mov[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int n, m, p, ans[N];
std::vector <std::vector <int> > map[4], dis;
std::vector <std::vector <bool> > vis;

struct node {
    int x, y;
} u, v;

struct queue {
    int l, r;
    node q[N];
    void pop() { l++; }
    void clear() { l = 0, r = -1; }
    node top() { return q[l % N]; }
    int size() { return r - l + 1; }
    void push(const node &a) { q[(++r) % N] = a; }
} q;

struct info {
    int xl, xr, yl, yr, id;
}; std::vector <info> vet;

template <class T> void resize(T &a, int n, int m) {
    for (int k = 0; k < 4; k++) {
        a.resize(n + 1);
        for (int i = 0; i <= n; i++) a[i].resize(m + 1);
    }
}

template <class T> void memset(T &a, int w, int xl, int xr, int yl, int yr) {
    for (int i = xl; i <= xr; i++)
        for (int j = yl; j <= yr; j++)
            a[i][j] = w;
}

void spfa(int xs, int ys, int xl, int xr, int yl, int yr) {
    memset(vis, 0, xl, xr, yl, yr);
    memset(dis, 1e9, xl, xr, yl, yr);
    q.clear(), q.push((node){xs, ys}), vis[xs][ys] = 1, dis[xs][ys] = 0;
    while (q.size()) {
        // printf("queue status [%d %d %d] [%d %d]\n", q.l, q.r, q.size(), q.top().x, q.top().y);
        u = q.top(), q.pop(), vis[u.x][u.y] = 0;
        // for (int i = xl; i <= xr; i++)
        //     for (int j = yl; j <= yr; j++)
        //         print(dis[i][j], " \n"[j == yr]);
        for (int t = 0, w; t < 4; t++) {
            v.x = u.x + mov[t][0], v.y = u.y + mov[t][1], w = map[t][u.x][u.y];
            if (v.x < xl || v.x > xr || v.y < yl || v.y > yr) continue;
            // printf("[%d %d] -> [%d %d] : %d\n", u.x, u.y, v.x, v.y, w);
            if (dis[u.x][u.y] + w < dis[v.x][v.y]) {
                dis[v.x][v.y] = dis[u.x][u.y] + w;
                // printf(">> %d %d %d\n", dis[v.x][v.y], (int)vis[v.x][v.y], q.r);
                if (!vis[v.x][v.y]) vis[v.x][v.y] = 1, q.push(v);
            }
        }
        // printf(">> %d %d : %d %d %d\n", u.x, u.y, q.size(), q.l, q.r);
    }
}

void solve(int xl, int xr, int yl, int yr, std::vector <info> vet) {
    if (xl > xr || yl > yr || !vet.size()) return;
    // printf(">> solve %d %d %d %d\n", xl, xr, yl, yr);
    std::vector <info> l_vet, r_vet;
    // if ((xr - xl + 1) > (yr - yl + 1)) {
        int mid = (xl + xr) >> 1;
        for (int i = yl; i <= yr; i++) {
            spfa(mid, i, xl, xr, yl, yr);
            for (std::vector <info> ::iterator it = vet.begin(); it != vet.end(); it++)
                ans[it->id] = std::min(ans[it->id], dis[it->xl][it->yl] + dis[it->xr][it->yr]);
        }
        for (std::vector <info> ::iterator it = vet.begin(); it != vet.end(); it++) {
            if (it->xl < mid && it->xr < mid) l_vet.push_back(*it);
            if (it->xl > mid && it->xr > mid) r_vet.push_back(*it);
        }
        solve(xl, mid - 1, yl, yr, l_vet), l_vet.clear();
        solve(mid + 1, xr, yl, yr, r_vet), r_vet.clear();
    // } else {
        
    // }
}

void main() {
    read(n), read(m), resize(dis, n, m), resize(vis, n, m);
    for (int i = 0; i < 4; i++) resize(map[i], n, m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < m; j++)
            read(map[0][i][j]), map[2][i][j + 1] = map[0][i][j];
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++)
            read(map[1][i][j]), map[3][i + 1][j] = map[1][i][j];
    // for (int i = 1; i <= n; i++)
    //     for (int j = 1; j <= m; j++)
    //         printf("[%d %d %d %d]%c", map[0][i][j], map[1][i][j], map[2][i][j], map[3][i][j], " \n"[j == m]);
    read(p);
    for (int i = 1; i <= p; i++) ans[i] = 1e9;
    for (int i = 1, xl, xr, yl, yr; i <= p; i++) {
        read(xl), read(yl), read(xr), read(yr);
        vet.push_back((info){xl, xr, yl, yr, i});
    } solve(1, n, 1, m, vet);
    for (int i = 1; i <= p; i++) print(ans[i], '\n');
}

} signed main() { return ringo::main(), 0; }