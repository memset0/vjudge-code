#include <bits/stdc++.h>

const int dx[2] = {1, 1};
const int dy[2] = {1, -1};

const int N = 1e3 + 5, M = N * N * 4;

int n, m, opt, ans, anc[M];
char c[N][N];
bool used[M];

int find(int u) {
    return anc[u] == u ? u : anc[u] = find(anc[u]);
}

char get(int i, int j) {
    if (i < 1 || j < 1) { return ' '; }
    return c[i][j];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int u = 0; u < M; u++) { anc[u] = u; }
    for (int i = 1; i <= n; i++) {
        scanf("%s", c[i] + 1);
        for (int j = 1; j <= m; j++) {
            if (c[i][j] == '/') { opt = i + j & 1 ^ 1; }
            if (c[i][j] == '\\') { opt = i + j & 1; }
        }
    }
    for (int i = 0; i <= n + 2; i++) {
        for (int j = 0; j <= m + 2; j++) {
            if (i + j & 1 ^ opt) {
                used[i * (m + 3) + j] = true;
                for (int k = 0; k < 2; k++) {
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (x < 0 || x > n + 2 || y < 0 || y > m + 2) { continue; }
                    if (k == 0 && get(i, j) == '/') { continue; }
                    if (k == 1 && get(i, j - 1) == '\\') { continue; }
                    int u = i * (m + 3) + j;
                    int v = x * (m + 3) + y;
                    u = find(u); v = find(v);
                    if (u != v) { anc[u] = v; }
                }
            }
        }
    }
    for (int u = 0; u < M; u++) { ans += used[u] && find(u) == u; }
    printf("%d\n", ans - 1);
    return 0;
}