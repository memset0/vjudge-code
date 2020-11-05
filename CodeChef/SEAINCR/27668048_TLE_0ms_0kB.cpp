// =================================
//   author: memset0
//   date: 2019.08.09 19:37:23
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define for_each(i, a) for (size_t i = 0, i##ed = a.size(); i < i##ed; ++i)
namespace ringo {
template <class T> inline void read(T &x) {
	x = 0; char c = getchar(); bool f = 0;
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
template <class T> inline void print(T a, int l, int r) { for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]); }

const int N = 1e6 + 10, M = N * 20;
int T, n, m, cnt, max, a[N], rt[N], val[M], lc[M], rc[M];
std::vector<std::pair<int, int>> q, vet[N];

void modify(int &u, int k, int w, int l, int r) {
	if (!u) u = ++cnt;
	val[u] = std::max(val[u], w);
	// printf("seg::modify %d %d %d %d %d : %d\n", u, k, w, l, r, val[u]);
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (k <= mid) modify(lc[u], k, w, l, mid);
	else modify(rc[u], k, w, mid + 1, r);
}

int query(int u, int ql, int qr, int l, int r) {
	// printf("seg::query %d %d %d %d %d : %d\n", u, ql, qr, l, r, val[u]);
	if (!u || ql > qr) return 0;
	if (ql == l && qr == r) return val[u];
	int mid = (l + r) >> 1;
	if (qr <= mid) return query(lc[u], ql, qr, l, mid);
	if (ql > mid) return query(rc[u], ql, qr, mid + 1, r);
	return std::max(query(lc[u], ql, mid, l, mid), query(rc[u], mid + 1, qr, mid + 1, r));
}

bool check(int mid, int ql, int qr) {
	// printf(">> check %d %d %d\n", mid, ql, qr);
	// return query(rt[mid], 1, qr, 1, n) >= ql;
	auto it = std::upper_bound(vet[mid].begin(), vet[mid].end(), std::make_pair(qr, 10000000));
	// printf(">> %d %d %d >> %d %d\n", mid, ql, qr, query(rt[mid], 1, qr, 1, n), it == vet[mid].begin() ? 0 : (std::prev(it))->second);
	return it == vet[mid].begin() ? false : std::prev(it)->second >= ql;
}
void main() {
	for (read(T); T--; ) {
		read(n), read(m);
		for (int i = 1; i <= n; i++) {
			read(a[i]), max = std::max(max, a[i]);
			q.push_back(std::make_pair(a[i], -i));
		}
		std::sort(q.begin(), q.end());
		for (auto it : q) {
			int i = -it.second, v = it.first;
			// printf("===== %d %d =====\n", it.first, it.second);
			modify(rt[1], i, i, 1, n);
			vet[1].push_back(std::make_pair(i, i));
			for (int j = 2, res; j <= v; j++) {
				modify(rt[j], i, res = query(rt[j - 1], 1, i - 1, 1, n), 1, n);
				// printf("query %d %d [%d] => %d\n", j - 1, i - 1, v, res);
				vet[j].push_back(std::make_pair(i, res));
			}
		}
		// print(rt, 1, max);
		for (int i = 1; i <= max; i++) {
			std::sort(vet[i].begin(), vet[i].end());
			for (int j = 1; j < vet[i].size(); j++)	
				vet[i][j].second = std::max(vet[i][j].second, vet[i][j - 1].second);
			// printf(">> [%d] [%d] >> ", i, vet[i].size());
			// for (int j = 0; j < vet[i].size(); j++)
			// 	printf("[%d %d]%c", vet[i][j].first, vet[i][j].second, " \n"[j == vet[i].size() - 1]);
		}
		for (int i = 1, l, r, ql, qr, mid, ans; i <= m; i++) {
			read(ql), read(qr), l = 1, r = max, ans = 0;
			while (l <= r) {
				// printf("check %d %d %d : %d\n", l, mid, r, check(mid = l + r >> 1, ql, qr));
				check(mid = (l + r) >> 1, ql, qr) ? (ans = mid, l = mid + 1) : (r = mid - 1);
			}
			print(ans, '\n');
		}
		memset(rt, 0, (max + 1) << 2);
		memset(lc, 0, (cnt + 1) << 2);
		memset(rc, 0, (cnt + 1) << 2);
		memset(val, 0, (cnt + 1) << 2);
		for (int i = 1; i <= max; i++) vet[i].clear();
		cnt = max = 0, q.clear();
	}
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);
#endif
	ringo::main();
	std::cerr << "clock: " << clock() / double(CLOCKS_PER_SEC) << std::endl;
}