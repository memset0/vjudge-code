// =================================
//   author: memset0
//   date: 2019.05.08 21:39:49
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 1e6 + 10, L = 21;
int n, m;
int a[N], del[N], use[N], log[N];
std::vector<int> v[N], G[N];

struct info {
	int val, id;
	inline info() {}
	inline info(int k) { val = a[k], id = k; }
	inline info(int a, int b) { val = a, id = b; }
};
std::vector<info> s, h, t, bkt[N];
std::priority_queue<int, std::vector<int>, std::greater<int>> q;

void noSolution() { puts("no"), exit(0); }

struct minimax {
	int min, max;
	inline minimax operator^(const minimax &other) const {
		return {std::min(min, other.min), std::max(max, other.max)};
	}
};

// namespace st {
// 	minimax st[L][N];
// 	inline minimax query(int l, int r) {
// 		int t = log[r - l + 1];
// 		// printf("query %d %d => %d => %d %d\n", l, r, t, l, r - (1 << t) + 1);
// 		return st[t][l] ^ st[t][r - (1 << t) + 1];
// 	}
// 	void init() {
// 		static int tmp[N];
// 		memset(tmp, 0, sizeof tmp);
// 		for (int i = 1; i <= m; i++) if (a[i]) {
// 			if (!tmp[a[i]]) tmp[a[i]] = i;
// 			st[0][i].min = tmp[a[i]];
// 		} else {
// 			st[0][i].min = i;
// 		}
// 		memset(tmp, 0, sizeof tmp);
// 		for (int i = m; i >= 1; i--) if (a[i]) {
// 			if (!tmp[a[i]]) tmp[a[i]] = i;
// 			st[0][i].max = tmp[a[i]];
// 		} else {
// 			st[0][i].max = i;
// 		}
// 		for (int i = 1; i < L; i++)
// 			for (int j = 1; j <= m; j++)
// 				if (j + (1 << (i - 1)) <= m)
// 					st[i][j] = st[i - 1][j] ^ st[i - 1][j + (1 << (i - 1))];
// 	}
// }
// using namespace st;

namespace seg {
	minimax b[N];
	struct node {
		int l, r, mid;
		minimax x;
	} p[N << 2];
	void build(int u, int l, int r) {
		p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
		if (l == r) { p[u].x = b[l]; return; }
		build(u << 1, l, p[u].mid);
		build(u << 1 | 1, p[u].mid + 1, r);
		p[u].x = p[u << 1].x ^ p[u << 1 | 1].x;
	}
	minimax query(int u, int l, int r) {
		if (p[u].l == l && p[u].r == r) return p[u].x;
		if (r <= p[u].mid) return query(u << 1, l, r);
		else if (l > p[u].mid) return query(u << 1 | 1, l, r);
		else return query(u << 1, l, p[u].mid) ^ query(u << 1 | 1, p[u].mid + 1, r);
	}
	void init() {
		static int tmp[N];
		memset(tmp, 0, sizeof tmp);
		for (int i = 1; i <= m; i++) if (a[i]) {
			if (!tmp[a[i]]) tmp[a[i]] = i;
			b[i].min = tmp[a[i]];
		} else {
			b[i].min = i;
		}
		memset(tmp, 0, sizeof tmp);
		for (int i = m; i >= 1; i--) if (a[i]) {
			if (!tmp[a[i]]) tmp[a[i]] = i;
			b[i].max = tmp[a[i]];
		} else {
			b[i].max = i;
		}
		build(1, 1, m);
		// for (int i = 1; i <= m; i++) print(b[i].min, " \n"[i == m]);
		// for (int i = 1; i <= m; i++) print(b[i].max, " \n"[i == m]);
		// for (int i = 1; i <= m; i++) print(query(1, i, i).min, " \n"[i == m]);
		// for (int i = 1; i <= m; i++) print(query(1, i, i).max, " \n"[i == m]);
	}
	minimax query(int l, int r) { return query(1, l, r); }
}
using namespace seg;

inline bool possible(int l, int r) {
	if (!((r - l + 1) & 1)) return false;
	if (l + 1 > r - 1) return true;
	auto it = query(l + 1, r - 1);
	// printf("possible %d %d => %d %d => %d\n", l, r, it.min, it.max, it.max <= r && it.min >= l);
	return it.max <= r && it.min >= l;
}

inline int newNode() {
	static int cur = 1;
	while (use[cur]) cur++;
	// printf(">> newNode => %d\n", cur);
	if (cur > n) std::cerr << "[No enougth nodes] No solution.\n", noSolution();
	return use[cur] = 1, cur;
}

void solve(int x) {
	// printf("solve %d\n", x);
	std::vector<std::pair<int, int>> jump;
	for (auto y : G[x]) {
		// printf("%d[%d %d] -> %d[%d %d] -> %d\n", x, *v[x].begin(), *--v[x].end(), y, *v[y].begin(), *--v[y].end(), *v[x].begin() < *v[y].begin() && *--v[x].end() < *--v[y].end());
		solve(y);
		jump.push_back(std::make_pair(*v[y].begin(), *--v[y].end()));
	}
	std::reverse(jump.begin(), jump.end());
	for (int i = 0, L, R, at = 0; i + 1 < v[x].size(); i++) {
		L = v[x][i], R = v[x][i + 1];
		// printf("solve %d -> [%d %d] | %d\n", x, L, R, at);
		// for (auto it : jump) printf("<%d %d> ", it.first, it.second); puts("");
		if (!((R - L + 1) & 1)) noSolution(); // 要求每个这样的区间为奇数
		s.clear(), s.push_back(info(L));
		for (int i = L + 1; i <= R - 1; i++) {
			s.push_back(info(i));
			// printf(">>>> %d : %d %d\n", i, at, at < jump.size() ? jump[at].first : -1);
			if (at < jump.size() && i == jump[at].first) i = jump[at++].second;
		}
		s.push_back(info(R));

		int c0 = 0, c1 = 0;
		for (int i = 1; i + 1 < s.size(); i++)
			s[i].val ? ++c1 : ++c0;
		if (c0 < c1 - 1) noSolution();

		int tl = 0, tr = s.size() - 1;
		while (tl < s.size() && s[tl].val) tl++;
		while (tr >= 0 && s[tr].val) tr--;
		if (tl == s.size()) continue;
		for (int i = tl; i <= tr; i++)
			if (s[i].val) {
				if (t.size() >= 2 && (--t.end())->val && !(----t.end())->val) {
					a[(----t.end())->id] = s[i].val;
					del[(----t.end())->id] = del[(--t.end())->id] = 1;
					t.pop_back(), t.pop_back(), t.push_back(s[i]);
				} else {
					t.push_back(s[i]);
				}
			} else {
				if (t.size() >= 2 && (--t.end())->val && (----t.end())->val) {
					a[s[i].id] = (----t.end())->val;
					del[s[i].id] = del[(--t.end())->id] = 1;
					t.pop_back();
				} else {
					t.push_back(s[i]);
				}
			}
		// print(a, L, R);

		// for (auto it : s) printf("[%d %d] ", it.val, it.id); puts("");
		t.clear(), std::swap(t, s);
		for (int i = 0; i < t.size(); i++)
			if (del[t[i].id]) del[t[i].id] = false;
			else s.push_back(t[i]);
		t.clear();
		// print(a, L, R);

		// for (auto it : s) printf("[%d %d] ", a[it.val], it.id); puts("");
		for (int i = 0, j = s.size() - 1; i <= j; ) {
			if (s[i].val) {
				h.push_back(s[i++]);
			} else if (s[j].val) {
				t.push_back(s[j--]);
			} else {
				if (h.size() >= 2) {
					a[s[i].id] = s[i].val = (----h.end())->val;
					h.pop_back(), i++;
				} else if (t.size() >= 2) {
					a[s[j].id] = s[j].val = (----t.end())->val;
					t.pop_back(), j--;
				} else {
					// for (auto it : h) printf("h -> %d %d\n", it.val, it.id);
					// for (auto it : t) printf("t -> %d %d\n", it.val, it.id);
					// printf(">> %d[%d %d] %d[%d %d]\n", i, s[i].id, s[i].val, j, s[j].id, s[j].val);
					a[s[i].id] = s[i].val = newNode();
					h.push_back(s[i++]);
				}
			}
		}
		h.clear(), t.clear(), s.clear();
		// for (auto it : s) printf("[%d %d] ", a[it.id], it.id); puts("");
		// print(a, L, R);
	}
}

void main() {
	read(n), m = (n << 1) - 1, log[0] = -1;
	for (int i = 1; i <= m; i++) log[i] = log[i >> 1] + 1;
	// printf("n = %d m = %d\n", n, m);
	for (int i = 1; i <= m; i++) {
		read(a[i]);
		if (a[i]) use[a[i]] = 1;
	}
	if (a[1] && a[m] && a[1] != a[m]) noSolution();
	else if (!a[1] && !a[m]) {
		init();
		int any = 0;
		// for (int i = 1; i <= m; i++) print(st[0][i].min, " \n"[i == m]);
		// for (int i = 1; i <= m; i++) print(st[0][i].max, " \n"[i == m]);
		for (int i = 3; i <= m - 2; i++) {
			if (a[i] && a[i] != a[2] && a[i] != a[m - 1] && possible(1, i) && possible(i, m))
				any = std::max(any, a[i]);
			// printf("%d -> %d %d\n", i, possible(1, i), possible(i, n));
		}
		std::cerr << "any = " << any << std::endl;
		a[1] = a[m] = any ? any : newNode();
	} else a[1] = a[m] = a[1] | a[m];
	init();
	for (int i = 1; i <= m; i++) if (a[i]) v[a[i]].push_back(i);
	for (int i = 1; i <= n; i++) if (v[i].size() > 1) {
		for (int j = 0; j + 1 < v[i].size(); j++)
			if (!possible(v[i][j], v[i][j + 1])) {
				std::cerr << "[Impossible section] " << v[i][j] << " " << v[i][j + 1] << std::endl;
				// for (int k = v[i][j]; k <= v[i][j + 1]; k++)
				// 	printf("a[%d] = %d -> %d %d\n", k, a[k], st[0][k].min, st[0][k].max);
				noSolution();
			}
		bkt[*--v[i].end()].push_back({*v[i].begin(), i});
	}
	for (int i = 1; i <= m; i++) {
		for (auto it : bkt[i]) {
			while (s.size() && (--s.end())->val >= it.val) {
				G[it.id].push_back((--s.end())->id);
				s.pop_back();
			}
			s.push_back(it);
		}
	}
	// for (auto it : s) printf("%d %d\n", it.val, it.id);
	s.clear();
	// print(a, 1, m, "a");
	solve(a[1]);
	puts("yes");
	print(a, 1, m);
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}