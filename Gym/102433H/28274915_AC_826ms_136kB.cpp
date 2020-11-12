#include <bits/stdc++.h>

inline int read() {
    char c, _c; int x; for (c = _c = getchar(); !isdigit(c); c = getchar()) { _c = c; }
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return _c == '-' ? -x : x;
}

const double eps = 1e-7, pi = acos(-1);

const int N = 2e3 + 5;

int n, ans, cnt[N];

struct Point {
    int x, y;
} p[N];

int main() {
    n = read();
    for (int i = 0; i < n; i++) { p[i].x = read(); p[i].y = read(); }
    for (int s = 0; s < n; s++) {
        for (int i = 0; i < n; i++) { cnt[i] = 0; }
        std::vector<double> d;
        for (int i = 0; i < n; i++) {
            if (s != i) {
                d.push_back(atan2(p[i].y - p[s].y, p[i].x - p[s].x));
                d.push_back(atan2(p[i].y - p[s].y, p[i].x - p[s].x) + pi + pi);
            }
        }
        d.push_back(1e5);
        std::sort(d.begin(), d.end());
        for (int i = (int) d.size() - 1; i >= 0; i--) { d[i] -= d[0]; }
        int j = 0, num = 1;
        for (; d[j + 1] < pi + eps; j++) { num++; }
        for (int i = 1; d[i] < pi + pi + eps; i++) {
            cnt[num]++; num--;
            for (; d[j + 1] < d[i] + pi + eps; j++) {
                cnt[num]++; num++;
            }
        }
        for (int i = 0; i <= n; i++) { ans = std::max(ans, cnt[i]); }
    }
    printf("%d\n", ans);
    return 0;
}