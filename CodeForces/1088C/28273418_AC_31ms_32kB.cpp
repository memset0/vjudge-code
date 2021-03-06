// =================================
//   author: memset0
//   date: 2018.12.06 19:13:51
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

const int N = 2e3 + 10;
int n;
ll a[N];

void main() {
    read(n);
    for (int i = 1; i <= n; i++)
        read(a[i]);
    printf("%d\n", n + 1);
    for (int i = n; i >= 1; i--) {
        int t = a[i] / n * n;
        int s = t - a[i];
        if (t < a[i]) s += n;
        s += i - 1;
        // printf(">> %d %d\n", a[i], s);
        for (int j = i; j >= 1; j--)
            a[j] += s;
        printf("1 %d %d\n", i, s);
    }
    // printf("=> ");
    // for (int i = 1; i <= n; i++)
    //     print(a[i], " \n"[i == n]);
    // printf("=> ");
    // for (int i = 1; i <= n; i++)  
    //     print(a[i] % n, " \n"[i == n]);
    printf("%d %d %d\n", 2, n, n);
}

} signed main() { return ringo::main(), 0; }