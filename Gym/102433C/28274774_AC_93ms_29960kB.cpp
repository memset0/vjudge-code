#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 1e6 + 5;

int n, m, dis[N];
std::vector<int> e[N];

void bfs(int s) {
    std::queue<int> que;
    memset(dis, 60, sizeof(dis)); dis[s] = 0;
    for (que.push(s); !que.empty(); que.pop()) {
        int u = que.front();
        for (auto v : e[u]) {
            if (dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                que.push(v);
            }
        }
    }
}

int main() {
    n = read(); m = read();
    for (int i = 0; i < m; i++) {
        int u = read(), v = read();
        e[u].push_back(v); e[v].push_back(u);
    }
    bfs(1);
    printf("%d\n", dis[n] - 1);
    return 0;
}