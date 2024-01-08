// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.07 16:15:49
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

const int N = 1e3 + 10;
const double inf = 1e30;
int n, ans, now;

struct node {
    int x, y;
    inline bool operator == (const node &other) const {
        return x == other.x && y == other.y;
    }
};
std::vector <node> a, b, c;

int solve() {
    int ans = 0, __1 = rand() % c.size(), __2 = rand() % c.size(); 
    node _1 = c[__1], _2 = c[__2];
    if (_1 == _2 || (__1 > a.size() && __2 > a.size())) { rand(); return 0; }
    if (_1.x == _2.x) {
        int min = -1e9 - 10, max = 1e9 + 10;
        for (auto u : b) u.x < _1.x ? min = std::max(min, u.x) : max = std::min(max, u.x);
        for (auto u : a) if (min <= u.x && u.x <= max) ++ans;
        rand();
    } else {
        double k = (_1.y - _2.y) / (double)(_1.x - _2.x);
        double _b = ((ll)_1.y * _2.x - (ll)_2.y * _1.x) / (double)(_2.x - _1.x);
        double min = -inf, max = inf;
        for (auto u : b) {
            double b = u.y - k * u.x;
            b < _b ? min = std::max(min, b) : max = std::min(max, b);
        }
        for (auto u : a) {
            double b = u.y - k * u.x;
            if (min <= b && b <= max) ++ans;
        }
    }
    return ans;
}

void main() {
    srand(20040725);
    read(n);
    for (int i = 1, x, y, c; i <= n; i++) {
        read(x), read(y), c = getchar();
        if (c == 'R') a.push_back((node){x, y});
        else b.push_back((node){x, y});
    }
    for (auto u : a) c.push_back(u);
    for (auto u : b) c.push_back(u);
    int limit = 130000000 / n;
    while (limit--) ans = std::max(ans, solve());
    print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }