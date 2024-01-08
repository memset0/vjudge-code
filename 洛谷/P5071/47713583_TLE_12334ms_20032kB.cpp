#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

// =================================
//   author: memset0
//   date: 2018.12.09 20:57:04
//   website: https://memset0.cn/
//   problem: 5071 [Ynoi2015]此时此刻的光辉
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

const int N = 1e5 + 10, M = sqrt(1e9) + 10, p = 19260817;
int n, m, ul, ur, ql, qr, now = 1, pos, max, sqn, limit;
int a[N], ans[N], bln[N], pri[N << 1], cnt[N << 1];
bool vis[M];
std::map < int, int > map;
int inv[N * 20];

struct pair {
	int first, second;
	pair () {}
	pair (int _first, int _second) { first = _first, second = _second; }
};
std::vector < pair > v[N];

struct query {
	int l, r, i;
	inline bool operator < (const query &other) const {
		if (bln[l] == bln[other.l]) return bln[l] & 1 ? r > other.r : r < other.r;
		return l < other.l;
	}
} q[N];

inline void pre(int a, std::vector < pair > &v) {
	int cnt = 0;
	for (int i = 1; pri[i] * pri[i] <= a && i <= pri[0]; i++)
		if (!(a % pri[i])) {
			cnt = 0;
			while (!(a % pri[i])) ++cnt, a /= pri[i];
			v.push_back(pair(i, cnt));
		}
	if (a != 1) {
		auto it = map.find(a);
		if (it == map.end()) map[a] = ++pos, pri[pos] = a, a = pos;
		else a = it->second;
		v.push_back(pair(a, 1));
	}
}

inline void add(int x) {
	for (auto u : v[x]) {
		now = (ll)now * inv[cnt[u.first] % p] % p;
		cnt[u.first] += u.second;
		now = (ll)now * cnt[u.first] % p;
	}
}

inline void del(int x) {
	for (auto u : v[x]) {
		now = (ll)now * inv[cnt[u.first] % p] % p;
		cnt[u.first] -= u.second;
		now = (ll)now * cnt[u.first] % p;
	}
}

void main() {
	read(n), read(m), sqn = sqrt(n);
	for (int i = 1; i <= n; i++) {
		read(a[i]), max = std::max(max, a[i]);
		bln[i] = (i - 1) / sqn;
	}
 	limit = sqrt(max);
	for (int i = 2; i <= limit; i++) {
		if (!vis[i]) pri[++pri[0]] = i, map[i] = pri[0];
		for (int j = 1; j <= pri[0] && i * pri[j] <= limit; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) break;
		}
	}
	pos = pri[0], max = 0;
	for (int i = 1; i <= n; i++) {
		pre(a[i], v[i]);
		for (auto u : v[i]) cnt[u.first] += u.second;
	}
	for (int i = 1; i <= pos; i++) max = std::max(max, cnt[i]);
	inv[0] = inv[1] = 1, limit = max + 1;
	for (int i = 2; i <= std::min(limit, p - 1); i++) inv[i] = (ll)(p - p / i) * inv[p % i] % p;
	for (int i = 1; i <= pos; i++) cnt[i] = 1;
	for (int i = 1; i <= m; i++) read(q[i].l), read(q[i].r), q[i].i = i;
	std::sort(q + 1, q + m + 1);
	ul = 1, ur = 0;
	for (int i = 1; i <= m; i++) {
		ql = q[i].l, qr = q[i].r;
		while (ul > ql) add(--ul);
		while (ur < qr) add(++ur);
		while (ul < ql) del(ul++);
		while (ur > qr) del(ur--);
		ans[q[i].i] = now;
	}
	for (int i = 1; i <= m; i++) print(ans[i], '\n');
}

} signed main() { return ringo::main(), 0; }