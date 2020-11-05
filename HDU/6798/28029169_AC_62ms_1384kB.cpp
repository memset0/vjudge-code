#include <bits/stdc++.h>

inline int read() {
    char c, _c; int x; for (c = _c = getchar(); !isdigit(c); c = getchar()) { _c = c; }
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return _c == '-' ? -x : x;
}

const double eps = 1e-6;
const double sqrt3 = sqrt(3);

int k;
double n, x, y, vx, vy, s, sx, sy;

long long solve(double t) {
    long long res = 0;
    s = y + vy * t;
    res += (long long) std::abs(floor(s / (sqrt3 * n / 2)));
    sx = x + vx * t + n / 2; sy = y + vy * t;
    res += (long long) std::abs(floor((sy + sqrt3 * sx) / (sqrt3 * n)));
    sx = x + vx * t - n / 2; sy = y + vy * t;
    res += (long long) std::abs(floor((sy - sqrt3 * sx) / (sqrt3 * n)));
    return res;
}

int main() {
    for (int T = read(); T; T--) {
        n = read(); x = read(); y = read(); vx = read(); vy = read(); k = read();
        double ans = 0;
        for (double l = 0, r = 2e10, mid; l + eps <= r; ) {
            mid = (l + r) / 2;
            if (solve(mid) >= k) {
                r = mid - eps; ans = mid;
            } else {
                l = mid + eps;
            }
        }
        printf("%.6f\n", ans);
    }
    return 0;
}