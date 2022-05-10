// luogu-judger-enable-o2
// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.04.08 23:03:34
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

const int N = 1e3 + 10;
int n, m, pos, hed_i, hed_d;
ll now, ans, dis[N][N];
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
} tmp[N];
std::vector <vector> qry[N];
std::pair <vector, ll> nod[N], q_i[N], q_d[N];
std::pair <vector, int> lie[N * N];

std::map <ll, int> map;
inline bool dmin(int a, int b, int c) { return dis[a][b] + dis[b][c] > dis[a][c]; }
inline bool dmax(int a, int b, int c) { return dis[a][b] + dis[b][c] < dis[a][c]; }
inline int calc(int x) { return x * (x - 1); }
inline void insert(const std::pair <vector, ll> &it) {
	// printf("insert [%d %d] %d\n", it.first.x, it.first.y, it.second);
	now -= calc(map[it.second]);
	++map[it.second];
	now += calc(map[it.second]);
}
inline void remove(const std::pair <vector, ll> &it) {
	// printf("remove [%d %d] %d\n", it.first.x, it.first.y, it.second);
	now -= calc(map[it.second]);
	--map[it.second];
	now += calc(map[it.second]);
}

void TMP() {
	std::map <std::pair <int, int> , int> map;
	for (int i = 1; i <= n; i++) {
		if (map[std::make_pair(p[i].x, p[i].y)]) {
			while(1) puts("CNMLGB");
		}
		map[std::make_pair(p[i].x, p[i].y)] = 1;
	}
}

void main() {
	read(n);
	for (int i = 1; i <= n; i++) read(p[i].x), read(p[i].y);
	TMP();
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
		// printf("===== u = %d (%d %d) =====\n", u, p[u].x, p[u].y);
		if (!qry[u].size()) continue;
		// if (u != 34) continue;

		int tmp = 0;
		for (int v = 1; v <= n; v++)
			if (v != u)
				nod[tmp++] = std::make_pair(vector(p[v], p[u]), dis[u][v]);
		std::sort(nod, nod + n - 1);

		std::map <std::pair <int, int> , int> map;
		map[std::make_pair(0, 1)] = map[std::make_pair(-1, 0)] = map[std::make_pair(1, 0)] = map[std::make_pair(0, -1)] = 0;
		for (int i = 0; i < qry[u].size(); i++)
			map[std::make_pair(-qry[u][i].y, qry[u][i].x)]++;
		m = 1, lie[0] = std::make_pair(vector(1, 0), map[std::make_pair(1, 0)]);
		for (std::map <std::pair <int, int> , int> ::iterator it = map.begin(); it != map.end(); it++)
			if (it->first.first != 1 || it->first.second != 0)
				lie[m++] = std::make_pair(vector(it->first.first, it->first.second), it->second);
		std::sort(lie + 1, lie + m);
		// for (int i = 0; i < n - 1; i++) printf("node %d %d : %lld\n", nod[i].first.x, nod[i].first.y, nod[i].second);
		// for (int i = 0; i < m; i++) printf("line %d %d\n", lie[i].first.x, lie[i].first.y, lie[i].second);

		pos = n - 1;
		while (nod[pos - 1].first.y <= 0 && pos) --pos;
		hed_i = hed_d = now = 0, ringo::map.clear();
		for (int i = 0; i < pos; i++) insert(nod[i]);
		for (int i = 0; i < n - 1; i++)
			q_i[i] = nod[(i + pos) % (n - 1)], q_d[i] = nod[i];
		
		// for (int i = 0; i < n - 1; i++) printf("[%d %d %lld]%c", q_i[i].first.x, q_i[i].first.y, q_i[i].second, " \n"[i == n - 2]);
		// for (int i = 0; i < n - 1; i++) printf("[%d %d %lld]%c", q_d[i].first.x, q_d[i].first.y, q_d[i].second, " \n"[i == n - 2]);
		tmp = 0;
		for (int i = 1; i < m; i++) {
			// printf("=> i = %d : [%d %d]\n", i, lie[i].x, lie[i].y);
			while (hed_i < (n - 1) && lie[i].first.rev() * q_i[hed_i].first < 0 && lie[i - 1].first.rev() * q_i[hed_i].first >= 0)
				insert(q_i[hed_i++]);
			while (hed_d < (n - 1) && lie[i].first * q_d[hed_d].first <= 0 && lie[i - 1].first * q_d[hed_d].first > 0)
				remove(q_d[hed_d++]);
			ans += (ll)now * lie[i].second;
			tmp += (ll)now * lie[i].second;
			// printf(">> ans += %lld * %d (%d %d)\n", now, lie[i].second, hed_i, hed_d);
		}
		// printf("%d -> %d\n", u, tmp);
		// printf("end u = %d\n", u);
	}
	print(ans, '\n');
}

} signed main() {
#ifdef MEMSET0_LOCAL_ENVIRONMENT
	freopen("1.in", "r", stdin);
#endif
	ringo::main();
	std::cerr << clock() / (double)CLOCKS_PER_SEC << std::endl;
	return 0;	
}