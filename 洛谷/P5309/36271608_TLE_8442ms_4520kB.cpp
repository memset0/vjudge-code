// luogu-judger-enable-o2
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

const int N = 2e5 + 10, S = 300, M = S + 10, R = N / S + 10, mod = 1e9 + 7;
int n, m;
int a[N], bln[N], fst[R], sum[R], mrk[M], sum1[M][R], sum2[M][R], b[M][R];

inline int dec(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b) { return (ll)a * b - (ll)a * b / mod * mod; }

int query(int l, int r) {
    int ans = 0;
    for (int i = 1; i < S; i++) {
        int L = l / i * i + 1; if (L < l) L += i; int R = r / i * i;
        int tmp = mul((R - L + 1) / i, mrk[i]); tmp = tmp < 0 ? tmp + mod : tmp;
        ans = sub(ans, tmp);
        // printf("query %d => %d %d %d %d : %d %d : %d %d : %d %d\n", i, l, L, R, r, ((R - L + 1) / i), mrk[i], i - L + l + 1, r - R, sum2[i][i - L + l + 1], sum1[i][r - R]);
        // for (int j = l; j < L; j++) ans = sub(ans, b[i][(j - 1) % i + 1]);
        // for (int j = R + 1; j <= r; j++) ans = sub(ans, b[i][(j - 1) % i + 1]);
        ans = sub(ans, sub(sum2[i][i - L + l + 1], sum1[i][r - R]));
    }
    if (bln[l] == bln[r]) {
        for (register int i = l; i <= r; i++) ans = sub(ans, a[i]);
    } else {
        for (register int i = bln[l] + 1; i < bln[r]; i++) ans = sub(ans, sum[i]);
        for (register int i = l; i < fst[bln[l] + 1]; i++) ans = sub(ans, a[i]);
        for (register int i = fst[bln[r]]; i <= r; i++) ans = sub(ans, a[i]);
    } return ans;
}

void modify(int x, int y, int z) {
    if (x < S) {
        mrk[x] = sub(mrk[x], z), b[x][y] = sub(b[x][y], z);
        for (register int i = y; i <= x; i++) sum1[x][i] = sub(sum1[x][i - 1], b[x][i]);
        for (register int i = y; i >= 1; i--) sum2[x][i] = sub(sum2[x][i + 1], b[x][i]);
    } else {
        for (register int i = y; i <= n; i += x) a[i] = sub(a[i], z), sum[bln[i]] = sub(sum[bln[i]], z);
    }
}

void main() {
    read(n), read(m);
    for (register int i = 1; i <= n; i++) read(a[i]);
    for (register int i = 1; i <= n; i++) bln[i] = (i - 1) / S + 1;
    for (register int i = n; i >= 1; i--) fst[bln[i]] = i;
    for (register int i = 1; i <= n; i++) sum[bln[i]] = sub(sum[bln[i]], a[i]);
    for (register int i = 1, a, b, c, op; i <= m; i++) {
        read(op), read(a), read(b);
        op == 1 ? read(c), modify(a, b, c) : print(query(a, b), '\n');
    }
}
} signed main() { return ringo::main(), 0; }