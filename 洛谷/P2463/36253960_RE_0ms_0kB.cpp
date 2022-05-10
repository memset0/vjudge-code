// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.29 15:59:13
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#define pb push_back
#define rep(i, l, r) for (register int i = l; i <= r; i++)

namespace ringo {
typedef long long ll;
typedef unsigned long long ull;
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
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 1010, M = 1010, L = N * M * 2;
int n, l, tn, siz, ans;
int a[N][M], m[N], fst[N], s[L], b[L], bkt[L], sa[L], rnk[L], tmp[L], height[L];

void SA_sort() {
	for (int i = 1; i <= siz; i++) bkt[i] = 0;
	for (int i = 1; i <= l; i++) ++bkt[rnk[i]];
	for (int i = 1; i <= siz; i++) bkt[i] += bkt[i - 1];
	for (int i = l; i >= 1; i--) sa[bkt[rnk[tmp[i]]]--] = tmp[i];
}

void SA() {
	siz = 1001;
	for (int i = 1; i <= n; i++) {
		fst[i] = l + 1;
		for (int j = 2; j <= m[i]; j++) s[++l] = a[i][j] - a[i][j - 1];
	}
	fst[n + 1] = l + 1;
	for (int i = 1; i <= l; i++) b[i] = s[i];
	std::sort(b + 1, b + l + 1), tn = std::unique(b + 1, b + l + 1) - b - 1;
	for (int i = 1; i <= l; i++) rnk[i] = std::lower_bound(b + 1, b + l + 1, s[i]) - b, tmp[i] = i;
	SA_sort();
	for (int len = 1, cnt = 0; cnt < l; len <<= 1, siz = cnt) {
		cnt = 0;
		for (int i = l; i >= l - len + 1; i--) tmp[++cnt] = i;
		for (int i = 1; i <= l; i++) if (sa[i] > len) tmp[++cnt] = sa[i] - len;
		SA_sort(), std::swap(rnk, tmp), rnk[sa[1]] = cnt = 1;
		for (int i = 2; i <= l; i++) rnk[sa[i]] = (tmp[sa[i - 1]] == tmp[sa[i]] && tmp[sa[i - 1] + len] == tmp[sa[i] + len]) ? cnt : ++cnt;
	}
	for (int i = 1, j, ans = 0; i <= l; i++) {
		if (ans) --ans; j = sa[rnk[i] - 1];
		while (s[i + ans] == s[j + ans]) ++ans;
		height[rnk[i]] = ans;
	}
}

bool check(int x) {
	for (int i = 2; i <= n; i++)
		if (height[i] < fst[x])
			return false;
	return true;
}

void main() {
	read(n);
	int min = -1;
	for (int i = 1; i <= n; i++) {
		read(m[i]), min = min == -1 || min > m[i] ? m[i] : min;
		for (int j = 1; j <= m[i]; j++) read(a[i][j]);
	}
	SA();
	// for (int i = 1; i <= l; i++) print(s[i], " \n"[i == l]);
	// for (int i = 1; i <= l; i++) print(sa[i], " \n"[i == l]);
	// for (int i = 1; i <= l; i++) print(rnk[i], " \n"[i == l]);
	// for (int i = 1; i <= l; i++) print(height[i], " \n"[i == l]);
	for (int l = 0, r = min - 1, mid = (l + r) >> 1; l <= r; mid = (l + r) >> 1)
		check(mid) ? (l = mid + 1, ans = mid) : (r = mid - 1);
	print(ans + 1, '\n');
}

} signed main() { return ringo::main(), 0; }