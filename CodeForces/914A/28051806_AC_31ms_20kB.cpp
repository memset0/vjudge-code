// =================================
//   author: memset0
//   date: 2018.12.05 18:57:44
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
namespace ringo {
typedef long long ll;

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

const int N = 1010;
int n, a[N], ans = -1e7;

bool check(int x) {
    int y = sqrt(x);
    return y * y != x;
}

void main() {
    read(n);
    for (int i = 1; i <= n; i++)  
        read(a[i]);
    for (int i = 1; i <= n; i++)
        if (check(a[i]))
            ans = std::max(ans, a[i]);
    print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }