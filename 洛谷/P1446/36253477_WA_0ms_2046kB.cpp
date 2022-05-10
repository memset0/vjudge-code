// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.02.14 11:04:08
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

const int N = 110;
int sr, sb, sg, m, p;

int inv(int x) { return x < 2 ? 1 : (ll)(p - p / x) * inv(p % x) % p; }
inline int fac(int n) { int ans = 1; while (n--) (ans *= n + 1) %= p; return ans; }

void main() {
	read(sr), read(sb), read(sg), read(m), read(p);
	print((ll)fac(sr + sb + sg) * inv(fac(sr)) * inv(fac(sb)) * inv(fac(sg)) * inv(m + 1) % p, '\n');
}

} signed main() { return ringo::main(), 0; }