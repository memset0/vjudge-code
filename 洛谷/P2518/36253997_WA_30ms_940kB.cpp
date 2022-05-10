// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.06 17:56:14
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
namespace ringo {
typedef long long ll;
typedef unsigned long long ull;

template < class T >
inline void read(T &x) {
    x = 0; register char c = getchar(); register bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
}

template < class T >
inline void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar('0' + x % 10);
}

template < class T >
inline void print(T x, char c) {
    print(x), putchar(c);
}

const int N = 60;
const ull p = 1ll << 63;
ll n, cnt[10];
ull ans, bkt[N];
std::vector < int > a;

inline void push(int x, int flag) {
    // printf("push %d %d\n", x, flag);
    for (int i = 1, t; i <= x; i++) {
        t = i;
        while (t % 2 == 0) bkt[2] += flag, t /= 2;
        while (t % 3 == 0) bkt[3] += flag, t /= 3;
        while (t % 5 == 0) bkt[5] += flag, t /= 5;
        while (t % 7 == 0) bkt[7] += flag, t /= 7;
    }
}

inline ull pull() {
    ull ret = 1;
    for (int i = 2; i < 8; i++)
        while (bkt[i]) {
            ret *= i;
            --bkt[i];
        }
    return ret;
}

inline void solve(int len) {
    memset(bkt, 0, sizeof(bkt));
    push(len, 1);
    for (int i = 0; i < 10; i++)
        push(cnt[i], -1);
    // printf("solve %d\n", len);
    // for (int i = 0; i < 10; i++) print(cnt[i], " \n"[i == 9]);
    // for (int i = 0; i < 10; i++) print(bkt[i], " \n"[i == 9]);
    ans += pull();
}

void main() {
    read(n);
    for (int t = n; t; t /= 10)
        a.push_back(t % 10);
    std::reverse(a.begin(), a.end());
    for (size_t i = 0; i < a.size(); i++) ++cnt[a[i]];
    for (size_t i = 0; i < a.size(); i++) {
        // printf("=== %d ===\n", i);
        for (int j = 0; j < a[i]; j++)
            if (cnt[j]) {
                --cnt[j];
                // printf(">>> %d %d\n", (int)i, j);
                solve(a.size() - i - 1);
                ++cnt[j];
            }
        --cnt[a[i]];
    }
    print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }