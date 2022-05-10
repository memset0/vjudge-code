// luogu-judger-enable-o2
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
//   date: 2019.01.11 19:26:36
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

const int N = 1e5 + 10, M = 350;
int n, m, tn, sqn, mod;
int a[N], b[N], bln[N], cnt[N], ans[N], _2[M], __2[M];
std::unordered_map <int, ll> map;

struct query {
	int l, r, p, i;
	inline bool operator < (const query &other) const {
		if (bln[l] != bln[other.l]) return l < other.l;
		return bln[l] & 1 ? r < other.r : r > other.r;
	}
} q[N];

inline int fpow(int b) {
	return (ll)__2[b / sqn] * _2[b % sqn] % mod;
}

inline void add(int x) {
	if (cnt[x]) {
		auto it = map.find(cnt[x]);
		it->second -= b[x];
		if (!it->second) map.erase(it);
	}
	++cnt[x];
	map[cnt[x]] += b[x];
}

inline void del(int x) {
	auto it = map.find(cnt[x]);
	it->second -= b[x];
	if (!it->second) map.erase(it);
	--cnt[x];
	if (cnt[x]) {
		map[cnt[x]] += b[x];
	}
}

void main() {
	read(n), read(m), sqn = n / (sqrt(m) * 2 / 3.0);
	for (int i = 1; i <= n; i++) read(a[i]), b[++tn] = a[i];
	std::sort(b + 1, b + tn + 1), tn = std::unique(b + 1, b + tn + 1) - b - 1;
	for (int i = 1; i <= n; i++) bln[i] = (i - 1) / sqn + 1;
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + tn + 1, a[i]) - b;
	for (int i = 1; i <= m; i++) read(q[i].l), read(q[i].r), read(q[i].p), q[i].i = i;
	std::sort(q + 1, q + m + 1), sqn = sqrt(n) + 1;
	int ul = 1, ur = 0; _2[0] = __2[0] = 1;
	for (int i = 1, l, r, sum; i <= m; i++) {
		l = q[i].l, r = q[i].r, mod = q[i].p;
		while (ul > l) add(a[--ul]);
		while (ur < r) add(a[++ur]);
		while (ul < l) del(a[ul++]);
		while (ur > r) del(a[ur--]);
		sum = 0;
		for (int i = 1; i <= sqn; i++) _2[i] = (_2[i - 1] << 1) % mod;
		for (int i = 1; i <= sqn; i++) __2[i] = (ll)__2[i - 1] * _2[sqn] % mod;
		for (auto it : map)
			sum = (sum + (ll)it.second % mod * (fpow(r - l + 1) - fpow(r - l + 1 - it.first))) % mod;
		ans[q[i].i] = (sum + q[i].p) % q[i].p;
	}
	for (int i = 1; i <= m; i++) print(ans[i], '\n');
}

} signed main() { return ringo::main(), 0; }