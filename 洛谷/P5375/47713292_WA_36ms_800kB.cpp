// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.15 17:57:49
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define debug(...) ((void)0)
#ifndef debug
#define debug(...) fprintf(stderr,__VA_ARGS__)
#endif
namespace ringo {
template <class T> inline void read(T &x) {
    x = 0; char c = getchar(); bool f = 0;
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
    if (s != "") std::cout << s << ": ";
    for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

int n, x, y, aF, bF, cF, dF;
std::deque<int> a;
std::vector<int> b;
std::set<int> c, d;

void main() {
    read(n), aF = bF = cF = dF = true;
    for (int i = 1; i <= n; i++)
        if (read(x), read(y), x == 1) {
            if (aF) a.push_back(y);
            if (bF) b.push_back(y);
            if (cF) c.insert(y);
            if (dF) d.insert(y);
        } else {
            // printf("%d %d %d %d\n", *a.begin(), *std::prev(b.end()), *std::prev(c.end()), *d.begin());
            if (aF && a.size()) { if (y != *a.begin()) aF = false; a.pop_front(); } else aF = false;
            if (bF && b.size()) { if (y != *std::prev(b.end())) bF = false; b.pop_back(); } else bF = false;
            if (cF && c.size()) { if (y != *std::prev(c.end())) cF = false; c.erase(std::prev(c.end())); } else cF = false;
            if (dF && d.size()) { if (y != *d.begin()) dF = false; d.erase(d.begin()); } else dF = false;
        }
    puts(aF ? "Yes" : "No"); puts(bF ? "Yes" : "No"); puts(cF ? "Yes" : "No"); puts(dF ? "Yes" : "No");
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
    freopen("1.in", "r", stdin);
#endif
    return ringo::main(), 0;
}