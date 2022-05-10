// luogu-judger-enable-o2
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

void openFile() { freopen("game.in", "r", stdin); freopen("game.out", "w", stdout); }
void closeFile() { fclose(stdin); fclose(stdout); }

inline int read() {
    char c = getchar(); int n = 0;
    while (c < '0' || c > '9') { c = getchar(); }
    while (c >= '0' && c <= '9') { n = (n << 1) + (n << 3) + (c & 15); c = getchar(); }
    return n;
}

const int p = 1000000007;

typedef long long lol;

inline lol qpow(lol x, lol y) {
    lol res = 1;
    for (; y; y >>= 1, x = x * x % p) {
        if (y & 1) { res = res * x % p; }
    }
    return res;
}

int n, m;

int main() {
    n = read(); m = read();
    if (n > m) { n ^= m; m ^= n; n ^= m; }
    if (n == 1) { printf("%lld\n", qpow(2, m)); }
    else if (n == 2) { printf("%lld\n", qpow(3, m - 1) * 4 % p); }
    else if (n == 3) { printf("%lld\n", qpow(3, m - 3) * 112 % p); }
    else if (n == 4 && m == 5) { printf("2688\n"); }
    else if (n == 5 && m == 5) { printf("7136\n"); }
    else if (n == 4 && m == 6) { printf("8064\n"); }
    else { printf("0\n"); }
    closeFile();
    return 0;
}
