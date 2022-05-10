// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.20 08:03:01
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

const int N = 2e6 + 10;
int n, siz, len, sa[N], rnk[N], tax[N], tmp[N];
char s[N];

void baseSort() {
	for (int i = 1; i <= siz; i++) tax[i] = 0;
	for (int i = 1; i <= len; i++) tax[rnk[i]]++;
	for (int i = 1; i <= siz; i++) tax[i] += tax[i - 1];
	for (int i = len; i >= 1; i--) sa[tax[rnk[tmp[i]]]--] = tmp[i];
}

void SA() {
	siz = 300;
	for (int i = 1; i <= len; i++) rnk[i] = s[i], tmp[i] = i;
	baseSort();
	for (int now = 1, cnt = 0; cnt < len; siz = cnt, now <<= 1) {
		cnt = 0;
		for (int i = len; i >= len - now + 1; i--) tmp[++cnt] = i;
		for (int i = 1; i <= len; i++) if (sa[i] > now) tmp[++cnt] = sa[i] - now	;
		baseSort(), std::swap(rnk, tmp), rnk[sa[1]] = cnt = 1;
		for (int i = 1; i <= len; i++) rnk[sa[i]] = tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + now] == tmp[sa[i - 1] + now] ? cnt : ++cnt;
	}
}

void main() {
	scanf("%s", s + 1), len = strlen(s + 1);
	SA();
	for (int i = 1; i <= len; i++) print(sa[i], " \n"[i == n]);
}

} signed main() { return ringo::main(), 0; }