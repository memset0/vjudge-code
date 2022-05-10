// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.26 20:36:02
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

const int N = 1e6 + 10;
int n; char s[N];

struct SA {
    static const int M = 4e6 + 10;
    int len, siz, tax[M], rnk[M], sa[M], tmp[M], height[M];
	void sort() {
		for (int i = 1; i <= siz; i++) tax[i] = 0;
		for (int i = 1; i <= len; i++) tax[rnk[i]]++;
		for (int i = 1; i <= siz; i++) tax[i] += tax[i - 1];
		for (int i = len; i >= 1; i--) sa[tax[rnk[tmp[i]]]--] = tmp[i];
	}
	void build(int n, char *s) {
		len = n, siz = 300;
		for (int i = 1; i <= len; i++) rnk[i] = s[i], tmp[i] = i;
		sort();
		for (int now = 1, cnt = 0; now < len; now <<= 1, siz = cnt, cnt = 0) {
			for (int i = len; i >= len - now + 1; i--) tmp[++cnt] = i;
			for (int i = 1; i <= len; i++) if (sa[i] > now) tmp[++cnt] = sa[i] - now;
			sort(), std::swap(rnk, tmp), rnk[sa[1]] = cnt = 1;
			for (int i = 2; i <= len; i++) rnk[sa[i]] = tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + now] == tmp[sa[i - 1] + now] ? cnt : ++cnt;
		}
	}
} sa;

void main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
    scanf("%s", s + 1), n = strlen(s + 1);
    sa.build(n, s);
    for (int i = 1; i <= n; i++) print(sa.sa[i], " \n"[i == n]);
    // for (int i = 2; i <= n; i++) print(sa.height[i], " \n"[i == n]);
}

} signed main() { return ringo::main(), 0; }