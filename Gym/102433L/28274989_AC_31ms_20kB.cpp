#include <bits/stdc++.h>

const int N = 1e2 + 5;

int n, w[N], dig[N], ans[N], now[N], tmp[N];
char str[N];
bool flag;

bool check() {
    for (int i = 0; i < n + n; i++) { tmp[i] = 0; }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tmp[i + j] = (tmp[i + j] + now[i] * now[j]) % 10;
        }
    }
    for (int i = 0; i < n + n; i++) {
        if (dig[i] != tmp[i]) { return false; }
    }
    return true;
}

void update() {
    if (!check()) { return; }
    if (flag) {
        for (int i = n - 1; i >= 0; i--) {
            if (ans[i] < now[i]) { return; }
            if (ans[i] > now[i]) { break; }
        }
    }
    flag = true;
    memcpy(ans, now, sizeof(int) * n);
}

void dfs(int d, int coef) {
    if (d == 14) { update(); return; }
    int sum = dig[d];
    for (int i = 1; i < d; i++) {
        sum = (sum + 10000 - now[i] * now[d - i]) % 10;
    }
    if (sum & 1) { return; }
    sum /= 2;
    for (int i = 0; i < 10; i++) {
        if (coef * i % 5 != sum) { continue; }
        now[d] = i;
        dfs(d + 1, coef);
    }
}

int main() {
    scanf("%s", str); n = strlen(str);
    for (int i = 0; i < n; i++) { dig[i] = str[n - 1 - i] - '0'; }
    if (n == 1 && dig[0] == 0) { printf("0\n"); return 0; }
    if (dig[0] == 0) {
        now[0] = 0; dfs(1, 0);
    }
    if (dig[0] == 1) {
        now[0] = 1; dfs(1, 1);
        now[0] = 9; dfs(1, 4);
    }
    if (dig[0] == 4) {
        now[0] = 2; dfs(1, 2);
        now[0] = 8; dfs(1, 3);
    }
    if (dig[0] == 5) {
        now[0] = 5; dfs(1, 0);
    }
    if (dig[0] == 6) {
        now[0] = 4; dfs(1, 4);
        now[0] = 6; dfs(1, 1);
    }
    if (dig[0] == 9) {
        now[0] = 3; dfs(1, 3);
        now[0] = 7; dfs(1, 2);
    }
    if (flag) {
        for (int i = n - 1; i >= 0; i--) {
            if (ans[i] > 0) { flag = false; }
            if (!flag) { printf("%d", ans[i]); }
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
    return 0;
}