// =================================
//   author: memset0
//   date: 2019.04.16 21:04:43
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define int long long
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

const int N = 4e5 + 10;
char str[N];
int n, m, cnt, tim, sqn, nod = 1, lst = 1;
std::vector<int> pre[N], son[N];
int fst[N], bln[N], length[N], sum0[N], sum1[N], sum2[N], f[N][20];
int end[N], dfn[N], len[N], siz[N], fa[N], ans[N], sl[N], sr[N], key[N], ch[N][27];

struct info {
	int i, j, k, id;
	inline bool operator < (const info &other) const {
		return i < other.i;
	}
} qry[N];

int append(int c) {
	// printf(">> append %d : %d %d\n", c, nod, lst);
	int u = ++nod, f = lst; lst = u, len[u] = len[f] + 1;
	while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
	if (!f) { fa[u] = 1; return u; }
	int s = ch[f][c];
	if (len[s] == len[f] + 1) { fa[u] = s; return u; }
	int p = ++nod; fa[p] = fa[s], fa[u] = fa[s] = p, len[p] = len[f] + 1;
	for (int i = 0; i <= 26; i++) ch[p][i] = ch[s][i];
	while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
	return u;
}

void dfs1(int u) {
	siz[u] = 1, dfn[u] = ++tim;
	for (auto v : son[u])
		dfs1(v), siz[u] += siz[v];
}

void dfs2(int u) {
	for (auto v : son[u])
		dfs2(v), sum0[u] += sum0[v];
}

inline void modify(int l, int r) {
	// printf("modify %d %d\n", l, r);
	if (bln[l] == bln[r]) {
		for (int i = l; i <= r; i++) ++sum1[i];
	} else {
		for (int i = l; i < fst[bln[l] + 1]; i++) ++sum1[i];
		for (int i = fst[bln[r]]; i <= r; i++) ++sum1[i];
		for (int i = bln[l] + 1; i < bln[r]; i++) ++sum2[i];
	}
}
inline int query(int k) {
	// printf("query %d => %d\n", k, sum1[k] + sum2[bln[k]]);
	return sum1[k] + sum2[bln[k]];
}

int jump(int u, int w) {
	// printf("jump %d %d : %d\n", u, w, len[u] - w);
	for (int i = 19; i >= 0; i--)
		if (w <= len[f[u][i]] && f[u][i])
			u = f[u][i];
	return u;
}

void main() {
	read(n), read(m), sqn = sqrt(n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", str + 1), length[i] = strlen(str + 1);
		sl[i] = cnt + 1, sr[i] = cnt + length[i];
		for (int j = 1; j <= length[i]; j++)
			key[++cnt] = append(str[j] - 'a');
		if (i != n) key[++cnt] = append(26);
	}
	for (int i = 2; i <= nod; i++) son[fa[i]].push_back(i);
	dfs1(1);
	// for (int i = 1; i <= cnt; i++) print(key[i], " \n"[i == cnt]);
	// for (int i = 1; i <= nod; i++) print(dfn[i], " \n"[i == nod]);
	// for (int i = 1; i <= nod; i++) print(siz[i], " \n"[i == nod]);
	for (int i = 1; i <= nod; i++) bln[i] = (i - 1) / sqn + 1;
	for (int i = nod; i >= 1; i--) fst[bln[i]] = i;
	for (int i = 1;	i <= nod; i++) f[i][0] = fa[i];
	for (int i = 1; i < 20; i++)
		for (int j = 1; j <= nod; j++)
			f[j][i] = f[f[j][i - 1]][i - 1];
	for (int i = 1; i <= n; i++) {
		end[i] = jump(key[sr[i]], sr[i] - sl[i] + 1);
		// printf("end[%d] = %d\n", i, end[i]);
	}
	for (int i = 1; i <= n; i++) if (length[i] > sqn) {
		memset(sum0, 0, sizeof(sum0));
		for (int j = sl[i]; j <= sr[i]; j++) sum0[key[j]] = 1;
		dfs2(1);
		pre[i].resize(n + 1);
		for (int j = 1; j <= n; j++) {
			pre[i][j] = pre[i][j - 1] + sum0[end[j]];
			// printf("%d -> %d\n", j, i, pre[i][j] - pre[i][j - 1]);
		}
	}
	for (int i = 1, l, r, k; i <= m; i++) {
		read(l), read(r), read(k);
		qry[(i << 1) - 1] = (info){l - 1, k, -1, i};
		qry[i << 1] = (info){r, k, 1, i};
	}
	std::sort(qry + 1, qry + (m << 1) + 1);
	for (int i = 1, now = 0, ans; ans = 0, i <= (m << 1); i++) if (qry[i].i) {
		// printf("===== %d [i=%d j=%d k=%d id=%d] =====\n", i, qry[i].i, qry[i].j, qry[i].k, qry[i].id);
		while (now < qry[i].i) {
			now++;
			modify(dfn[end[now]], dfn[end[now]] + siz[end[now]] - 1);
		}
		if (length[qry[i].j] > sqn) {
			ans = pre[qry[i].j][qry[i].i];
		} else {
			for (int j = sl[qry[i].j]; j <= sr[qry[i].j]; j++)
				ans += query(dfn[key[j]]);
		}
		// printf(">>> (%d) %d\n", length[qry[i].j] > sqn, ans);
		ringo::ans[qry[i].id] += qry[i].k * ans;
	}
	for (int i = 1; i <= m; i++) print(ans[i], '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}