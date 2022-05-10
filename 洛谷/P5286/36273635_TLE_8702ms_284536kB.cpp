// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.08 23:03:34
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

const int N = 1e3 + 10;
int n, m, pos, hed_i, hed_d;
ll now, ans, dis[N][N];
bool flag1, flag2, flag3;
std::vector <int> todo[N], vet[N][N];

struct node {
	int x, y;
} p[N];

struct vector {
	int x, y;
	inline vector() {}
	inline vector(int _x, int _y) { x = _x, y = _y; }
	inline vector(const node &a, const node &b) { x = a.x - b.x, y = a.y - b.y; }

	inline vector rev() { return vector(-x, -y); }
	inline short get_c() const {
		if (x >= 0 && y > 0) return 0;
		if (x < 0 && y >= 0) return 1;
		if (x <= 0 && y < 0) return 2;
		if (x > 0 && y <= 0) return 3;
	}
	inline ll operator * (const vector &other) const { return (ll)x * other.y - (ll)other.x * y; }
	inline bool operator < (const vector &other) const {
		if (get_c() != other.get_c()) return get_c() < other.get_c();
		ll xgzc = (*this) * other;
		return xgzc == 0 ? (x == other.x ? y < other.y : x < other.x) : xgzc > 0;
	}
} tmp[N], lie[N * N];
std::vector <vector> qry[N];
std::pair <vector, ll> nod[N], q_i[N], q_d[N];

std::map <ll, int> map;
inline bool dmin(int a, int b, int c) { return dis[a][b] + dis[b][c] > dis[a][c]; }
inline bool dmax(int a, int b, int c) { return dis[a][b] + dis[b][c] < dis[a][c]; }
inline int calc(int x) { return x * (x - 1); }
inline void insert(const std::pair <vector, ll> &it) {
	now -= calc(map[it.second]);
	++map[it.second];
	now += calc(map[it.second]);
}
inline void remove(const std::pair <vector, ll> &it) {
	now -= calc(map[it.second]);
	--map[it.second];
	if (map[it.second] < 0) puts("!!!!!!!!!!!!!!!!!!!!!!!!");
	now += calc(map[it.second]);
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(p[i].x), read(p[i].y);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			dis[i][j] = dis[j][i] = (ll)(p[i].x - p[j].x) * (p[i].x - p[j].x) + (ll)(p[i].y - p[j].y) * (p[i].y - p[j].y);
	for (int u = 1; u <= n; u++) {
		std::map <int, std::vector <int> > map;
		for (int v = 1; v <= n; v++) if (u != v) map[dis[u][v]].push_back(v);
		for (std::map <int, std::vector <int> > ::iterator it = map.begin(); it != map.end(); it++) {
			std::vector <int>& now = it->second;
			if (now.size() > 1) {
				for (int i = 0; i < now.size(); i++)
					for (int j = 0; j < now.size(); j++) if (i != j)
						vet[now[i]][now[j]].push_back(u);
			}
		}
	}
	for (int u = 1; u <= n; u++)
		for (int v = 1; v <= n; v++) if (u != v && vet[u][v].size() > 1) {
			for (int i = 0; i < vet[u][v].size(); i++)
				for (int j = 0; j < vet[u][v].size(); j++) if (i != j) {
					int p = vet[u][v][i], q = vet[u][v][j];
					if (dmin(u, p, q) && dmin(u, q, p) && dmin(v, p, q) && dmin(v, q, p)) {
						qry[q].push_back(vector(ringo::p[p], ringo::p[q]));
						// printf("u=%d v=%d p=%d q=%d\n", u, v, p, q);
					}
				}
		}
	for (int u = 1; u <= n; u++) {
		m = qry[u].size(); if (!m) continue;
		// printf("===== u = %d (%d %d) =====\n", u, p[u].x, p[u].y);
		int tmp = 0;
		for (int v = 1; v <= n; v++) if (v != u) nod[tmp++] = std::make_pair(vector(p[v], p[u]), dis[u][v]);
		for (int i = 0; i < m; i++) lie[i + 1] = vector(-qry[u][i].y, qry[u][i].x);
		// printf("before sort nod\n");
		std::sort(nod, nod + n - 1);
		// printf("before sort lie\n");
		lie[++m] = vector(-1, 0), lie[++m] = vector(0, 1), lie[++m] = vector(0, -1);
		std::sort(lie + 1, lie + m + 1);
		++m, lie[0] = vector(1, 0);
		// printf("after all sort\n");
		// for (int i = 0; i < n - 1; i++) printf("nod %d %d : %lld\n", nod[i].first.x, nod[i].first.y, nod[i].second);
		// for (int i = 0; i < m; i++) printf("lie %d %d\n", lie[i].x, lie[i].y);

		pos = n - 1;
		while (nod[pos - 1].first.y <= 0 && pos) --pos;
		hed_i = hed_d = now = 0, map.clear();
		// printf(">>> pos = %d\n", pos);
		for (int i = 0; i < pos; i++) insert(nod[i]);
		// printf(">>> now = %d\n", now);
		for (int i = 0; i < n - 1; i++) q_i[i] = nod[(i + pos) % (n - 1)], q_d[i] = nod[i];
		
		flag1 = flag2 = flag3 = 1;
		// for (int i = 0; i < n - 1; i++) printf("[%d %d %lld]%c", q_i[i].first.x, q_i[i].first.y, q_i[i].second, " \n"[i == n - 2]);
		// for (int i = 0; i < n - 1; i++) printf("[%d %d %lld]%c", q_d[i].first.x, q_d[i].first.y, q_d[i].second, " \n"[i == n - 2]);
		for (int i = 1; i < m; i++) {
			// printf("=> i = %d : [%d %d]\n", i, lie[i].x, lie[i].y);
			while (hed_i < (n - 1) && lie[i].rev() * q_i[hed_i].first < 0 && lie[i - 1].rev() * q_i[hed_i].first >= 0) insert(q_i[hed_i++]);
			// printf(">> %d %d\n", lie[i] * q_d[hed_d].first, lie[i - 1] * q_d[hed_d].first);
			// printf(">> %d %d\n", lie[i] * q_d[hed_d + 1].first, lie[i - 1] * q_d[hed_d + 1].first);
			while (hed_d < (n - 1) && lie[i] * q_d[hed_d].first <= 0 && lie[i - 1] * q_d[hed_d].first > 0) remove(q_d[hed_d++]);
			ans += now;
			if (lie[i].x == 0 && lie[i].y == 1 && flag1) flag1 = 0, ans -= now;
			if (lie[i].x == -1 && lie[i].y == 0 && flag2) flag2 = 0, ans -= now;
			if (lie[i].x == 0 && lie[i].y == -1 && flag3) flag3 = 0, ans -= now;
			// printf(">> ans += %lld (%d %d)\n", now, hed_i, hed_d);
		}
		// printf("end u = %d\n", u);
	}
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}