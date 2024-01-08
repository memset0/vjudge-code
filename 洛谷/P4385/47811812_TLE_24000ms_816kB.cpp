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
const double inf = 1e18;
int n, ans, now;

struct node {
    int x, y;
    inline bool operator == (const node &other) const {
        return x == other.x && y == other.y;
    }
};
std::vector <node> a, b;

int solve() {
    auto _1 = a[rand() % a.size()], _2 = a[rand() % a.size()];
    if (_1 == _2) return 0;
    auto k = (_1.y - _2.y) / (double)(_1.x - _2.x);
    auto _b = ((ll)_1.y * _2.x - (ll)_2.y * _1.x) / (double)(_2.x - _1.x);
    auto min = -inf, max = inf;
    int ans = 0;
    for (auto u : b) {
        double b = u.y - k * u.x;
        b < _b ? min = std::max(min, b) : max = std::min(max, b);
    }
    for (auto u : a) {
        double b = u.y - k * u.x;
        if (min <= b && b <= max) ++ans;
    }
    return ans;
}

void main() {
    srand(20040214);
    read(n);
    for (int i = 1, x, y, c; i <= n; i++) {
        read(x), read(y), c = getchar();
        if (c == 'R') a.push_back((node){x, y});
        else b.push_back((node){x, y});
    }
    int limit = 100000000 / n;
    while (limit--) ans = std::max(ans, solve());
    print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }