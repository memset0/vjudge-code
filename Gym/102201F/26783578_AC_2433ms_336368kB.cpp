#include <bits/stdc++.h>
using namespace std;
#define PII pair<int, int>
#define VI vector<int>
#define VPII vector<PII>
#define LL long long
#define LD long double
#define f first
#define s second
#define MP make_pair
#define PB push_back
#define endl '\n'
#define ALL(c) (c).begin(), (c).end()
#define SIZ(c) (int)(c).size()
#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, b, e) for (int i = (b); i <= (int)(e); ++i)
#define FORD(i, b, e) for (int i = (b); i >= (int)(e); --i)
#define st f
#define nd s
#define pb PB
#define mp MP
#define eb emplace_back
#define siz(c) SIZ(c)
template<class n, class s> ostream& operator<<(ostream& p, pair<n, s> x) {
	return p << "<" << x.f << ", " << x.s << ">";
}
template<class n>
auto operator<<(ostream& p, n y) -> typename enable_if<!is_same<n, string>::value, decltype(y.begin(), p)>::type {
	int o = 0;
	p << "{";
	for (auto c : y) {
		if (o++) p << ", ";
		p << c;
	}
	return p << "}";
}
void dor() { cerr << endl; }
template<class n, class... s> void dor(n p, s... y) {
	cerr << p << " ";
	dor(y...);
}
template<class n, class s> void mini(n& p, s y) {
	if (p > y) p = y;
}
template<class n, class s> void maxi(n& p, s y) {
	if (p < y) p = y;
}
#ifdef DEB
#	define debug(...) dor(__FUNCTION__, ":", __LINE__, ": ", __VA_ARGS__)
#else
#	define debug(...)
#endif
#define I(x) #x " = ", (x), " "
#define A(a, i) #a "[" #i " = ", i, "] = ", a[i], " "
const int MXN = 250005;
int t[MXN];
VI V[MXN];
namespace lca {
const int mlog = 20;
int jump[MXN][mlog + 1];
int odl[MXN];
void dfs(int x, int pop) {
	odl[x] = odl[pop] + 1;
	jump[x][0] = pop;
	FOR(i, 1, mlog - 1) { jump[x][i] = jump[jump[x][i - 1]][i - 1]; }
	REP(i, V[x].size()) {
		if (V[x][i] == pop) continue;
		dfs(V[x][i], x);
	}
}
int query(int a, int b) {
	if (odl[a] < odl[b]) swap(a, b);
	FORD(i, mlog - 1, 0) {
		if (odl[jump[a][i]] >= odl[b]) { a = jump[a][i]; }
	}
	FORD(i, mlog - 1, 0) {
		if (jump[a][i] != jump[b][i]) {
			a = jump[a][i];
			b = jump[b][i];
		}
	}
	if (a != b) {
		a = jump[a][0];
		b = jump[b][0];
	}
	return a;
}
};	// namespace lca
int raa = 22;
VI cand[MXN];
VI cnt[MXN];
PII qq[MXN];
int ll[MXN];
int len[MXN];
VI que[MXN];
VI sta;
int R(int a, int b) { return rand() % (b - a + 1) + a; }
void dfs2(int v, int pp) {
	sta.PB(v);
	for (auto i : que[v]) {
		int last = sta.size() - 1;
		int ile = lca::odl[v] - lca::odl[ll[i]] + 1;
		int first = last - ile + 1;
		REP(u, raa) { cand[i].PB(t[sta[R(first, last)]]); }
	}
	for (auto i : V[v])
		if (i != pp) dfs2(i, v);
	sta.pop_back();
}
vector<pair<PII, int>> query[MXN];
int IL[MXN];
void dfs3(int v, int pp) {
	IL[t[v]]++;
	for (auto i : query[v]) {
		int vv = i.f.f;
		int ii = i.f.s;
		int add = i.s;
		int col = cand[vv][ii];
		cnt[vv][ii] += add * IL[col];
		if (add == -2 && t[v] == col) cnt[vv][ii]++;
	}
	for (auto i : V[v])
		if (i != pp) dfs3(i, v);
	IL[t[v]]--;
}
int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	FOR(i, 1, n) { scanf("%d", &t[i]); }
	REP(i, n - 1) {
		int a, b;
		scanf("%d%d", &a, &b);
		V[a].PB(b);
		V[b].PB(a);
	}
	lca::dfs(1, 0);
	REP(i, q) {
		int a, b;
		scanf("%d%d", &a, &b);
		int r = lca::query(a, b);
		qq[i] = MP(a, b);
		ll[i] = r;
		que[a].PB(i);
		que[b].PB(i);
		len[i] = lca::odl[a] + lca::odl[b] - 2 * lca::odl[r] + 1;
		debug(a, b, r, len[i]);
	}
	dfs2(1, 0);
	REP(i, q) {
		sort(ALL(cand[i]));
		cand[i].resize(unique(ALL(cand[i])) - cand[i].begin());
		cnt[i].resize(cand[i].size());
		REP(j, cand[i].size()) {
			query[ll[i]].PB(MP(MP(i, j), -2));
			query[qq[i].f].PB(MP(MP(i, j), 1));
			query[qq[i].s].PB(MP(MP(i, j), 1));
		}
	}
	dfs3(1, 0);
	REP(i, q) {
		int ans = -1;
		debug(i, I(cand[i]));
		REP(j, cand[i].size()) {
			if (cnt[i][j] * 2 > len[i]) ans = cand[i][j];
		}
		printf("%d\n", ans);
	}
}