// luogu-judger-enable-o2
// luogu-judger-enable-o2
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

const int N = 1e5 + 10, M = 210, mov[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int n, m, p, ans[N];

std::vector <std::vector <int> > map[4], dis;
// std::vector <std::vector <int> > map_1[4], dis_1;
// int map_2[4][M][M], dis_2[M][M];

struct node {
    int x, y;
} u, v;

struct status {
    node u; int w;
    inline bool operator < (const status &other) const {
        return w > other.w;
    }
} now; std::priority_queue <status> q;

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
    memset(dis, 1e9, xl, xr, yl, yr);
    q.push((status){(node){xs, ys}, 0}), dis[xs][ys] = 0;
    while (q.size()) {
        now = q.top(), u = now.u, q.pop(); if (now.w != dis[now.u.x][now.u.y]) continue;
        for (int t = 0, w; t < 4; t++) {
            v.x = u.x + mov[t][0], v.y = u.y + mov[t][1], w = map[t][u.x][u.y];
            if (v.x < xl || v.x > xr || v.y < yl || v.y > yr) continue;
            if (dis[u.x][u.y] + w < dis[v.x][v.y]) {
                dis[v.x][v.y] = dis[u.x][u.y] + w;
                q.push((status){v, dis[v.x][v.y]});
            }
        }
    }
}

void solve(int xl, int xr, int yl, int yr, std::vector <info> vet) {
    if (xl > xr || yl > yr || !vet.size()) return;
    // printf(">> solve %d %d %d %d\n", xl, xr, yl, yr);
    std::vector <info> l_vet, r_vet;
    if ((xr - xl + 1) * (yr - yl + 1) < 100) {
        for (std::vector <info> ::iterator it = vet.begin(); it != vet.end(); it++) {
            spfa(it->xl, it->yl, xl, xr, yl, yr);
            ans[it->id] = std::min(ans[it->id], dis[it->xr][it->yr]);
        } return;
    }
    if ((xr - xl + 1) > (yr - yl + 1)) {
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
    } else {
        int mid = (yl + yr) >> 1;
        for (int i = xl; i <= xr; i++) {
            spfa(i, mid, xl, xr, yl, yr);
            for (std::vector <info> ::iterator it = vet.begin(); it != vet.end(); it++)
                ans[it->id] = std::min(ans[it->id], dis[it->xl][it->yl] + dis[it->xr][it->yr]);
        }
        for (std::vector <info> ::iterator it = vet.begin(); it != vet.end(); it++) {
            if (it->yl < mid && it->yr < mid) l_vet.push_back(*it);
            if (it->yl > mid && it->yr > mid) r_vet.push_back(*it);
        }
        solve(xl, xr, yl, mid - 1, l_vet), l_vet.clear();
        solve(xl, xr, mid + 1, yr, r_vet), r_vet.clear();
    }
}

void main() {
    read(n), read(m), resize(dis, n, m);
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
