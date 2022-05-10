// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.05.05 15:40:11
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
template <class T> inline void print(T *a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 4e5 + 10, M = 8e5 + 10, B = 1e4;
int n, m, t, nod, c_uid;
std::bitset<B> tmp, bit[N];
int tot = 2, hed[N], nxt[M], to[M];
std::map<std::pair<int, int>, int> map;
std::vector<std::pair<int, int>> same[N];
int q[N], tag[N], lst[N], ans[N], ind[N], now[N];

inline void addEdge(int u, int v) {
	// printf("%d %d\n", u, v);
	// printf("add edge %d -> %d\n", u, v);
	++ind[v], nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++;
}

#define getCid(x, b) ((x) << 1) - 1 + (b)
inline int getUid(int x, int t) {
	auto it = map.find(std::make_pair(x, t));
	if (it == map.end()) {
		int res = ++c_uid;
		map[std::make_pair(x, t)] = res;
		same[x].push_back(std::make_pair(t, res));
		// printf("get uid %d %d => %d\n", x, t, res);
		return res;
	} else return it->second;
}

void main() {
	read(t), read(n), read(m);
	// printf("> %d %d %d\n", t, n, m);
	for (int i = 1, x, y, t, op, X, Y; i <= m; i++) {
		read(op), read(t), read(x), read(y);
		// printf("%d %d %d %d >> %d %d >> %d %d %d %d\n", op, t, x, y, X, Y, getCid(X, 0), getCid(X, 1), getCid(Y, 0), getCid(Y, 1));
		if (!op) {
			X = getUid(x, t), Y = getUid(y, t + 1);
			addEdge(getCid(X, 0), getCid(Y, 0));
			addEdge(getCid(Y, 1), getCid(X, 1));
		} else {
			X = getUid(x, t), Y = getUid(y, t);
			addEdge(getCid(X, 1), getCid(Y, 0));
			addEdge(getCid(Y, 1), getCid(X, 0));
		}
	}
	for (int i = 1; i <= n; i++) {
		std::sort(same[i].begin(), same[i].end());
		for (int j = 1; j < same[i].size(); j++) {
			addEdge(getCid(same[i][j - 1].second, 0), getCid(same[i][j].second, 0));
			addEdge(getCid(same[i][j].second, 1), getCid(same[i][j - 1].second, 1));
		}
		// for (int j = 0; j < same[i].size(); j++)
		// 	printf("%d %d : %d %d\n", i, j, same[i][j].first, same[i][j].second);
		if (same[i].size()) lst[i] = (--same[i].end())->second;
		else lst[i] = -1;
	}
	nod = c_uid << 1;
	for (int L = 1, R = std::min(B, n), u, l, r; L <= n; L = R + 1, R = std::min(L + B - 1, n)) {
		l = 1, r = 0;
		for (int i = 1; i <= nod; i++) bit[i].reset();
		for (int i = L; i <= R; i++) if (~lst[i]) bit[getCid(lst[i], 1)].set(i - L);
		for (int i = 1; i <= nod; i++) { now[i] = ind[i]; if (!ind[i]) q[++r] = i; }
		while (l <= r) {
			u = q[l++];
			// printf(">> %d\n", u);
			for (int i = hed[u], v; v = to[i], i; i = nxt[i]) {
				bit[v] |= bit[u];
				if (!--now[v]) q[++r] = v;
			}
		}
		// for (int i = 1; i <= nod; i++) {
		// 	for (int j = 1; j <= n; j++)
		// 		print(bit[i][j - 1], " \n"[j == n]);
		// }
		tmp.reset();
		for (int i = L; i <= R; i++)
			if (~lst[i] && bit[getCid(lst[i], 0)][i - L]) {
				tag[i] = 1;
				tmp.set(i - L);
			}
		// for (int i = 1; i <= n; i++) print(tmp[i - 1], " \n"[i == n]);
		for (int i = 1; i <= n; i++)
			if (~lst[i]) {
				ans[i] += (bit[getCid(lst[i], 0)] | tmp).count();
			} else {
				ans[i] += tmp.count();
			}
	}
	// for (int i = 1; i <= n; i++) print(lst[i], " \n"[i == n]);
	// for (int i = 1; i <= n; i++) print(tag[i], " \n"[i == n]);
	for (int i = 1; i <= n; i++) print(tag[i] ? 0 : n - ans[i] - 1, " \n"[i == n]);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}