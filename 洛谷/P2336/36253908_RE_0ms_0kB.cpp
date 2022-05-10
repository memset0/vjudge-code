// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.02 10:03:49
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define int long long
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

const int N = 2e5 + 2e3 + 10;
int n, m, t, x, len, siz, st[N][20];
typedef int array[N];
array s, sa, rnk, tmp, fst, tax, lst, cnt, bln, pre, sum, log, ans1, ans2, height;
std::vector <int> a[N], b[N];

struct info { int id, l; };
std::vector <info> qry[N];

inline void modify(int k, int x) { for (; k <= len; k += k & -k) sum[k] += x; }
inline int query(int k) { int s = 0; for (; k; k -= k & -k) s += sum[k]; return s; }
inline int query(int l, int r) { return query(r) - query(l - 1); }
int query_min(int l, int r) { int t = log[r - l + 1]; return std::min(st[l][t], st[r - (1 << t) + 1][t]); }

void base_sort() {
	for (int i = 1; i <= siz; i++) tax[i] = 0;
	for (int i = 1; i <= len; i++) tax[rnk[i]]++;
	for (int i = 1; i <= siz; i++) tax[i] += tax[i - 1];
	for (int i = len; i >= 1; i--) sa[tax[rnk[tmp[i]]]--] = tmp[i];
}

void get_sa() {
	for (int i = 1; i <= len; i++) rnk[i] = s[i], tmp[i] = i;
	base_sort();
	for (int now = 1, cnt = 0; cnt < len; siz = cnt, now <<= 1) {
		cnt = 0;
		for (int i = len; i >= len - now + 1; i--) tmp[++cnt] = i;
		for (int i = 1; i <= len; i++) if (sa[i] > now) tmp[++cnt] = sa[i] - now;
		base_sort(), std::swap(rnk, tmp), rnk[sa[1]] = cnt = 1;
		for (int i = 2; i <= len; i++) rnk[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + now] == tmp[sa[i - 1] + now]) ? cnt : ++cnt;
	}
}

void get_height() {
	for (int i = 1, j, ans = 0; i <= n; i++) {
		j = sa[rnk[i] - 1]; if (ans) --ans;
		while (s[i + ans] == s[j + ans]) ans++;
		height[rnk[i]] = ans;
	}
}

int search_l(int _l, int _r) {
	int l = _l, r = _r, mid, ans = -1;
	while (l <= r)
		if (query_min((mid = (l + r) >> 1), _r) >= height[_r])
			ans = mid, l = mid + 1;
		else r = mid - 1;
	return ans;
}

int search_r(int _l, int _r ) {
	int l = _l, r = _r, mid, ans = -1;
	while (l <= r)
		if (query_min(_l, (mid = (l + r) >> 1)) >= height[_l])
			ans = mid, r = mid - 1;
		else l = mid + 1;
	return ans;
}

void main() {
	read(n), read(m), siz = 1e4;
	for (int i = 1; i <= n; i++) {
		read(t), s[++len] = ++siz;
		// printf("[%d] %d\n", i, t);
		for (int j = 1; j <= t; j++) {
			read(x), a[i].push_back(x);
			s[++len] = x, bln[len] = i;
		}
	}
	for (int i = 1; i <= m; i++) {
		read(t), s[++len] = ++siz, fst[i] = len + 1;
		// printf("[%d] %d\n", i, t);
		for (int j = 1; j <= t; j++) {
			read(x), b[i].push_back(x);
			s[++len] = x;
		}
	}
	get_sa(), get_height();
	// for (int i = 1; i <= len; i++) print(s[i], " \n"[i == len]);
	// for (int i = 1; i <= len; i++) print(height[i], " \n"[i == len]);
	for (int i = 1; (1 << i) <= len; i++) log[1 << i] = i;
	for (int i = 1; i <= len; i++) if (!log[i]) log[i] = log[i - 1];
	for (int i = 1; i <= len; i++) st[i][0] = height[i];
	for (int i = 1; i < 20; i++)
		for (int j = 1; (1 << i) + j - 1 <= len; j++)
			st[j][i] = std::min(st[j][i - 1], st[j + (1 << i)][i - 1]);
	for (int i = 1, l, r; i <= m; i++) {
		l = search_l(1, fst[i]), r = search_r(fst[i], len);
		// printf(">> %d %d %d\n" , i, l, r);
		qry[r].push_back((info){l, i}), ++cnt[l];
	}
	for (int i = 1; i <= len; i++) {
		if (!bln[i]) continue;
		if (lst[bln[i]]) pre[i] = lst[bln[i]];
		lst[bln[i]] = i;
	}
	for (int i = 1; i <= len; i++) {
		if (pre[i]) modify(pre[i], -1);
		modify(i, 1);
		for (std::vector <info> ::iterator it = qry[i].begin(); it != qry[i].end(); it++)
			ans1[it->id] = query(it->l, i);
	}
	memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= len; i++) {
		modify(i, cnt[i]);
		if (bln[i]) ans2[bln[sa[i]]] += query(pre[i] + 1, i);
		for (std::vector <info> ::iterator it = qry[i].begin(); it != qry[i].end(); it++)
			modify(it->l, -1);
	}
	for (int i = 1; i <= m; i++) print(ans1[i], '\n');
	for (int i = 1; i <= n; i++) print(ans2[i], " \n"[i == n]);
}

} signed main() { return ringo::main(), 0; }