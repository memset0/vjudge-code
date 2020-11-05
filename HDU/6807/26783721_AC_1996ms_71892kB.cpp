#include <bits/stdc++.h>

const double eps = 1e-7, Eps = 3e-7;

const int N = 3e6 + 5;

int T, n, m;
double ans;
std::multiset<double> s[5];

struct Element {
    int d;
    double x, b;
} e[N];

bool operator <(const Element &i, const Element &j) {
    if (std::abs(i.x - j.x) < Eps) { return i.d > j.d; }
    return i.x < j.x;
}

inline double get(double x) {
    return x >= 360 - eps ? x - 360 : x;
}

void insert(double l, double r, int d) {
    if (d == 1) {
        if (r >= 360 - eps) {
            r -= 360;
            e[m++] = (Element) {d, l, -l};
            e[m++] = (Element) {-d, 360.0, -l};
            e[m++] = (Element) {d, 0.0, 360 - l};
            e[m++] = (Element) {-d, r, 360 - l};
        } else {
            e[m++] = (Element) {d, l, -l};
            e[m++] = (Element) {-d, r, -l};
        }
    } else if (d == 2) {
        if (r >= 360 - eps) {
            r -= 360;
            e[m++] = (Element) {d, l, 180 + l};
            e[m++] = (Element) {-d, 360.0, 180 + l};
            e[m++] = (Element) {d, 0.0, 180 - (360 - l)};
            e[m++] = (Element) {-d, r, 180 - (360 - l)};
        } else {
            e[m++] = (Element) {d, l, 180 + l};
            e[m++] = (Element) {-d, r, 180 + l};
        }
    } else if (d == 3) {
        if (r >= 360 - eps) {
            r -= 360;
            e[m++] = (Element) {d, l, -l * 12};
            e[m++] = (Element) {-d, 360.0, -l * 12};
            e[m++] = (Element) {d, 0.0, (360 - l) * 12};
            e[m++] = (Element) {-d, r, (360 - l) * 12};
        } else {
            e[m++] = (Element) {d, l, -l * 12};
            e[m++] = (Element) {-d, r, -l * 12};
        }
    } else {
        if (r >= 360 - eps) {
            r -= 360;
            e[m++] = (Element) {d, l, 180 + l * 12};
            e[m++] = (Element) {-d, 360.0, 180 + l * 12};
            e[m++] = (Element) {d, 0.0, 180 - (360 - l) * 12};
            e[m++] = (Element) {-d, r, 180 - (360 - l) * 12};
        } else {
            e[m++] = (Element) {d, l, 180 + l * 12};
            e[m++] = (Element) {-d, r, 180 + l * 12};
        }
    }
}

inline double getk(int d) {
    switch (d) {
        case 1: { return -1; }
        case 2: { return 1; }
        case 3: { return -12; }
        case 4: { return 12; }
    }
}

inline double query(double x) {
    double res = 0;
    if (!s[1].empty()) { res = std::max(res, *s[1].rbegin() + x); }
    if (!s[2].empty()) { res = std::max(res, *s[2].rbegin() - x); }
    if (!s[3].empty()) { res = std::max(res, *s[3].rbegin() + x * 12); }
    if (!s[4].empty()) { res = std::max(res, *s[4].rbegin() - x * 12); }
    return res;
}

int main() {
    for (scanf("%d", &T); T; T--) {
        scanf("%d", &n); m = 0;
        for (int i = 0; i < n; i++) {
            int hh, mm, ss;
            scanf("%d:%d:%d", &hh, &mm, &ss);
            hh %= 12;
            double ha, ma;
            ma = (mm * 6 + ss * 0.1);
            ha = (hh * 30 + ma / 12.0);
            double l = ha, r;
            for (int i = 0; i < 2; l = get(r), i++) {
                r = l + 180;
                insert(l, r, i % 2 == 0 ? 1 : 2);
            }
            l = ha;
            for (int i = 0; i < 24; l = get(r), i++) {
                r = l + 15;
                insert(l, r, i % 2 == 0 ? 3 : 4);
            }
        }
        ans = 180;
        std::sort(e, e + m);
        double l = -1, r;
        for (int i = 0, j; i < m; i = j) {
            if (l != -1) {
                r = e[i].x;
                ans = std::min(ans, query(l));
                ans = std::min(ans, query(r));
                for (int p = 1; p <= 4; p++) {
                    if (s[p].empty()) { continue; }
                    for (int q = p + 1; q <= 4; q++) {
                        if (s[q].empty()) { continue; }
                        double x = (*s[p].rbegin() - *s[q].rbegin()) / (getk(p) - getk(q));
                        if (l <= x && x <= r) { ans = std::min(ans, query(x)); }
                    }
                }
            }
            for (j = i; j < m && std::abs(e[i].x - e[j].x) < Eps; j++) {    
                l = e[j].x;
                if (e[j].d > 0) {
                    s[e[j].d].insert(e[j].b);
                } else {
                    s[-e[j].d].erase(s[-e[j].d].find(e[j].b));
                }
            }
        }
        printf("%.8f\n", ans);
    }
    return 0;
}

// 1231321312321