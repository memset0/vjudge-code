// =================================
//   author: memset0
//   date: 2019.04.11 20:10:02
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

const int N = 2e5 + 10;
char s[N];
int n, m, a[N], l[N], r[N], ans[N];
std::vector<std::pair<int, int>> qry[N];

namespace bit {
	int max[N];
	inline void modify(int k, int x) {
		if (!k) return;
		// printf("bit::modify %d %d\n", k, x);
		for (int i = k; i; i -= i & -i)
			max[i] = std::max(max[i], x);
	}
	inline int query(int k) {
		// printf("bit::query %d\n", k);
		int ans = 0;
		for (int i = k; i <= n; i += i & -i)
			ans = std::max(ans, max[i]);
		return ans;
	}
}

namespace lct {
    int fa[N], val[N], key[N], tag[N], sum[N], ch[N][2]; bool rev[N];
    inline bool getSon(int x) { return ch[fa[x]][1] == x; }
    inline bool isRoot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
	inline void pushup(int x, int v) { tag[x] = key[x] = v; }
    inline void pushdown(int x) { if (tag[x]) pushup(ch[x][0], tag[x]), pushup(ch[x][1], tag[x]), tag[x] = 0; }
    inline void rotate(int x) {
        if (!x || !fa[x]) return;
        int f = fa[x], fs = getSon(x), ff = fa[f], ffs = getSon(f), y = ch[x][fs ^ 1];
        if (!isRoot(f)) ch[ff][ffs] = x;
		ch[x][fs ^ 1] = f, ch[f][fs] = y, fa[y] = f, fa[f] = x, fa[x] = ff;
    }
    inline void clean(int x) { if (!isRoot(x)) clean(fa[x]); pushdown(x); }
    inline void splay(int x) {
        clean(x);
        for (int f = fa[x]; !isRoot(x); rotate(x), f = fa[x])
            if (!isRoot(f)) rotate(getSon(x) == getSon(f) ? f : x);
    }
	inline void access(int x) {
		// lct access 的时候在树状数组里更新答案
		for (int y = 0; x; y = x, x = fa[x]) {
			splay(x), ch[x][1] = y;
			bit::modify(key[x], val[x]);
		}
	}
}

namespace sam {
	int nod = 1, lst = 1, len[N], fa[N], ch[N][2];
	inline void append(int c) {
		int u = ++nod, f = lst; lst = u, len[u] = len[f] + 1;
		while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
		if (!f) { fa[u] = 1; return; }
		int s = ch[f][c];
		if (len[s] == len[f] + 1) { fa[u] = s; return; }
		int p = ++nod; fa[p] = fa[s], fa[u] = fa[s] = p, len[p] = len[f] + 1;
		ch[p][0] = ch[s][0], ch[p][1] = ch[s][1];
		while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
	}
	void build() {
		for (int i = 1; i <= n; i++) append(s[i] - '0'), a[i] = lst;
		for (int i = 1; i <= nod; i++) lct::val[i] = len[i], lct::fa[i] = fa[i];
	}
	void debug() {
		printf("a[] ");
		for (int i = 1; i <= n; i++) print(a[i], " \n"[i == n]);
		printf("fa[] ");
		for (int i = 1; i <= nod; i++) print(fa[i], " \n"[i == nod]);
		printf("len[] ");
		for (int i = 1; i <= nod; i++) print(len[i], " \n"[i == nod]);
	}
}

void main() {
	read(n), read(m), scanf("%s", s + 1);
	sam::build();
	// sam::debug();
	for (int i = 1; i <= m; i++) {
		read(l[i]), read(r[i]);
		qry[r[i]].push_back(std::make_pair(l[i], i));
	}
	for (int i = 1; i <= n; i++) {
		// printf("===== %d =====\n", i);
		lct::access(a[i]), lct::splay(a[i]), lct::pushup(a[i], i);
		for (const auto &it : qry[i]) ans[it.second] = bit::query(it.first);
	}
	for (int i = 1; i <= m; i++) print(ans[i], '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}
