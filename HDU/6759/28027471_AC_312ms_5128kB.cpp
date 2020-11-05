#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 1e5 + 5;

int T, n, m, vol, ans, stc[N];
std::map<std::pair<int, int>, int> map;

struct Point {
    int x, y;
} a[N], p[N];

bool operator <(Point p, Point q) {
    return p.x == q.x ? p.y < q.y : p.x < q.x;
}

inline double getSlope(int i, int j) {
    return p[i].x == p[j].x ? 1e18 : (double) (p[j].y - p[i].y) / (p[j].x - p[i].x);
}

int main() {
    for (scanf("%d", &T); T; T--) {
        scanf("%d", &n);
        map.clear();
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &a[i].x, &a[i].y);
            map[{a[i].x, a[i].y}]++;
        }
        m = 0;
        for (int i = 0; i < n; i++) {
            p[m++] = a[i];
        }
        std::sort(p, p + m);
        vol = 0;
        for (int i = 0; i < m; i++) {
            if (i < m - 1 && p[i].x == p[i + 1].x) { continue; }
            for (; vol >= 2 && 1ll * (p[stc[vol]].y - p[stc[vol - 1]].y) * (p[i].x - p[stc[vol]].x) <= 1ll * (p[stc[vol]].x - p[stc[vol - 1]].x) * (p[i].y - p[stc[vol]].y); vol--);
            stc[++vol] = i;
        }
        ans = 0;
        for (int i = 1; i < vol; i++) {
            if (p[stc[i]].y > p[stc[i + 1]].y) {
                ans += map[{p[stc[i]].x, p[stc[i]].y}] == 1;
            }
        }
        if (vol > 0) {
            ans += map[{p[stc[vol]].x, p[stc[vol]].y}] == 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}