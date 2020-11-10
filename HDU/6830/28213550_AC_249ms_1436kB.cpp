#include <bits/stdc++.h>

inline int read() {
    char c, _c; int x; for (c = _c = getchar(); !isdigit(c); c = getchar()) { _c = c; }
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return _c == '-' ? -x : x;
}

struct Point {
    int x, y;
};

bool operator <(const Point &u, const Point &v) {
    return u.x == v.x ? u.y < v.y : u.x < v.x;
}

struct Vector {
    int x, y;
};

Vector operator >>(const Point &u, const Point &v) {
    return (Vector) {v.x - u.x, v.y - u.y};
}
long long operator ^(const Vector &u, const Vector &v) {
    return 1ll * u.x * v.y - 1ll * u.y * v.x;
}

inline long long get(Point u, Point v, Point w) {
    return ((u >> v) ^ (u >> w));
}

int T, n;
long long ans;
std::vector<Point> p[3], up[3], vp[3];

void build(std::vector<Point> p, std::vector<Point> &up, std::vector<Point> &vp) {
    std::sort(p.begin(), p.end());
    up.clear(); up.push_back(p[0]);
    for (int i = 1; i < p.size(); i++) {
        while (true) {
            int top = up.size();
            if (top <= 1) { break; }
            top--;
            if (((up[top - 1] >> up[top]) ^ (up[top] >> p[i])) < 0) { break; }
            up.pop_back();
        }
        up.push_back(p[i]);
    }
    vp.clear(); vp.push_back(p[0]);
    for (int i = 1; i < p.size(); i++) {
        while (true) {
            int top = vp.size();
            if (top <= 1) { break; }
            top--;
            if (((vp[top - 1] >> vp[top]) ^ (vp[top] >> p[i])) > 0) { break; }
            vp.pop_back();
        }
        vp.push_back(p[i]);
    }
}

void solve() {
    int res;
    ans = 0;
    for (auto u : p[0]) {
        for (auto v : p[1]) {
            res = 0;
            for (int l = 1, r = (int) up[2].size() - 1, mid; l <= r; ) {
                mid = l + r >> 1;
                if (get(u, v, up[2][mid - 1]) < get(u, v, up[2][mid])) {
                    l = mid + 1; res = mid;
                } else {
                    r = mid - 1;
                }
            }
            for (int i = res - 2; i <= res + 2; i++) {
                if (i >= 0 && i < up[2].size()) {
                    ans = std::max(ans, std::abs(get(u, v, up[2][i])));
                }
            }
            res = 0;
            for (int l = 1, r = (int) up[2].size() - 1, mid; l <= r; ) {
                mid = l + r >> 1;
                if (get(u, v, up[2][mid - 1]) > get(u, v, up[2][mid])) {
                    l = mid + 1; res = mid;
                } else {
                    r = mid - 1;
                }
            }
            for (int i = res - 2; i <= res + 2; i++) {
                if (i >= 0 && i < up[2].size()) {
                    ans = std::max(ans, std::abs(get(u, v, up[2][i])));
                }
            }
            res = 0;
            for (int l = 1, r = (int) vp[2].size() - 1, mid; l <= r; ) {
                mid = l + r >> 1;
                if (get(u, v, vp[2][mid - 1]) > get(u, v, vp[2][mid])) {
                    l = mid + 1; res = mid;
                } else {
                    r = mid - 1;
                }
            }
            for (int i = res - 2; i <= res + 2; i++) {
                if (i >= 0 && i < vp[2].size()) {
                    ans = std::max(ans, std::abs(get(u, v, vp[2][i])));
                }
            }
            res = 0;
            for (int l = 1, r = (int) vp[2].size() - 1, mid; l <= r; ) {
                mid = l + r >> 1;
                if (get(u, v, vp[2][mid - 1]) < get(u, v, vp[2][mid])) {
                    l = mid + 1; res = mid;
                } else {
                    r = mid - 1;
                }
            }
            for (int i = res - 2; i <= res + 2; i++) {
                if (i >= 0 && i < vp[2].size()) {
                    ans = std::max(ans, std::abs(get(u, v, vp[2][i])));
                }
            }
        }
    }
}

int main() {
    for (int T = read(); T; T--) {
        n = read();
        p[0].clear(); p[1].clear(); p[2].clear();
        for (int i = 0; i < n; i++) {
            int x = read(), y = read(), c = read();
            p[c].push_back((Point) {x, y});
        }
        build(p[0], up[0], vp[0]);
        build(p[1], up[1], vp[1]);
        build(p[2], up[2], vp[2]);
        if (up[2].size() + vp[2].size() < up[0].size() + vp[0].size()) {
            std::swap(up[0], up[2]); std::swap(vp[0], vp[2]);
        }
        if (up[2].size() + vp[2].size() < up[1].size() + vp[1].size()) {
            std::swap(up[1], up[2]); std::swap(vp[1], vp[2]);
        }
        p[0].clear();
        for (auto u : up[0]) { p[0].push_back(u); }
        for (auto u : vp[0]) { p[0].push_back(u); }
        p[1].clear();
        for (auto u : up[1]) { p[1].push_back(u); }
        for (auto u : vp[1]) { p[1].push_back(u); }
        solve();
        if (ans % 2 == 0) {
            printf("%lld.0\n", ans / 2);
        } else {
            printf("%lld.5\n", ans / 2);
        }
    }
    return 0;
}