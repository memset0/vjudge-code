#pragma GCC diagnostic error "-std=c++11"
#pragma GCC target("avx")
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

const int N = 2e5 + 10, M = N * 150;
int m, v, x, y, z, k, w, l, r, op, cnt, rt[N];
ll ans;

struct node {
	int rnd, val, siz, ch[2];
	bool rev;
	ll sum;
} p[M];

int merge(int, int); void update(int);
inline int new_node(int v) { int u = ++cnt; p[u].val = v; p[u].rnd = rand(); return update(u), u; }
inline int merge(int x, int y, int z) { return merge(x, merge(y, z)); }

void update(int u) {
	p[u].siz = p[p[u].ch[0]].siz + p[p[u].ch[1]].siz + 1;
	p[u].sum = p[p[u].ch[0]].sum + p[p[u].ch[1]].sum + p[u].val;
}

void pushup(int &u) {
	p[++cnt] = p[u], u = cnt;
	p[u].rev ^= 1;
	std::swap(p[u].ch[0], p[u].ch[1]);
}

void pushdown(int &u) {
	if (!p[u].rev || !u) return;
	// p[++cnt] = p[u], u = cnt;
	if (p[u].ch[0]) pushup(p[u].ch[0]);
	if (p[u].ch[1]) pushup(p[u].ch[1]);
	p[u].rev = 0;
}

int merge(int x, int y) {
	int u;
	if (!x && !y) return 0;
	if (!x || !y) return p[u = ++cnt] = p[x | y], u;
	if (p[x].rnd < p[y].rnd) {
		pushdown(x);
		u = x;
		p[u].ch[1] = merge(p[x].ch[1], y);
	} else {
		pushdown(y);
		u = y;
		p[u].ch[0] = merge(x, p[y].ch[0]);
	}
	return update(u), u;
}

void split(int u, int k, int &x, int &y) {
	if (!u) return (void)(x = y = 0);
	pushdown(u);
	if (k <= p[p[u].ch[0]].siz) {
		p[y = ++cnt] = p[u];
		split(p[y].ch[0], k, x, p[y].ch[0]);
		update(y);
	} else {
		p[x = ++cnt] = p[u];
		split(p[x].ch[1], k - p[p[u].ch[0]].siz - 1, p[x].ch[1], y);
		update(x);
	}
}

void dfs(int u) {
	pushdown(u);
	if (p[u].ch[0]) dfs(p[u].ch[0]);
	printf("%d(%lld) ", p[u].val, p[u].sum);
	if (p[u].ch[1]) dfs(p[u].ch[1]);
}

void main() {
	srand(20040725);
	read(m);
	for (int i = 1; i <= m; i++) {
		read(v), read(op);
		if (op == 1) {
			read(k), read(w), k ^= ans, w ^= ans;
			// printf(">>> [%d] %d %d %d %d\n", i, v, op, k, w);
			split(rt[v], k, x, y);
			rt[i] = merge(x, new_node(w), y);
		} else if (op == 2) {
			read(k), k ^= ans;
			// printf(">>> [%d] %d %d %d\n", v, i, op, k);
			split(rt[v], k - 1, x, y), split(y, 1, y, z);
			rt[i] = merge(x, z);
		} else if (op == 3) {
			read(l), read(r), l ^= ans, r ^= ans;
			// printf(">>> [%d] %d %d %d %d\n", i, v, op, l, r);
			split(rt[v], l - 1, x, y), split(y, r - l + 1, y, z);
			pushup(y), rt[i] = merge(x, y, z);
		} else {
			read(l), read(r), l ^= ans, r ^= ans;
			// printf(">>> [%d] %d %d %d %d\n", i, v, op, l, r);
			split(rt[v], l - 1, x, y), split(y, r - l + 1, y, z);
			print(ans = p[y].sum, '\n'), rt[i] = rt[v];
		}
		// dfs(rt[i]), putchar('\n');
		// std::cerr << cnt << std::endl;
	}
}

} signed main() { return ringo::main(), 0; }