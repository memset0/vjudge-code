// Author -- Frame
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
#define Finline __inline__ __attribute__((always_inline))
#define DEBUG fprintf(stderr, "Running on Line %d in Function %s\n", __LINE__, __FUNCTION__)
#define SZ(x) ((int)x.size())
#define mkpr std::make_pair
#define pb push_back
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef std::pair<int, int> pi;
typedef std::pair<ll, ll> pl;
using std::max;
using std::min;
const int inf = 0x3f3f3f3f, Inf = 0x7fffffff;
const ll INF = 0x3f3f3f3f3f3f3f3f;
Finline uint rnd() {
	static uint seed = 416;
	return seed ^= seed >> 5, seed ^= seed << 17, seed ^= seed >> 13;
}
template<typename _Tp> _Tp gcd(const _Tp& a, const _Tp& b) { return (!b) ? a : gcd(b, a % b); }
template<typename _Tp> Finline _Tp abs(const _Tp& a) { return a >= 0 ? a : -a; }
template<typename _Tp> Finline void chmax(_Tp& a, const _Tp& b) { (a < b) && (a = b); }
template<typename _Tp> Finline void chmin(_Tp& a, const _Tp& b) { (b < a) && (a = b); }
template<typename _Tp> Finline void read(_Tp& x) {
	char ch(getchar());
	bool f(false);
	while (!isdigit(ch)) f |= ch == 45, ch = getchar();
	x = ch & 15, ch = getchar();
	while (isdigit(ch)) x = (((x << 2) + x) << 1) + (ch & 15), ch = getchar();
	f && (x = -x);
}
template<typename _Tp, typename... Args> Finline void read(_Tp& t, Args&... args) {
	read(t);
	read(args...);
}
template<typename _Tp, typename... Args> Finline _Tp min(const _Tp& a, const _Tp& b, const Args&... args) {
	return a < b ? min(a, args...) : min(b, args...);
}
template<typename _Tp, typename... Args> Finline _Tp max(const _Tp& a, const _Tp& b, const Args&... args) {
	return a < b ? max(b, args...) : max(a, args...);
}
Finline int read_str(char* s) {
	char ch(getchar());
	while (ch == ' ' || ch == '\r' || ch == '\n') ch = getchar();
	char* tar = s;
	*tar = ch, ch = getchar();
	while (ch != ' ' && ch != '\r' && ch != '\n' && ch != EOF) *(++tar) = ch, ch = getchar();
	return tar - s + 1;
}

const int N = 100005;
const int block_val = 3500;
int n, m, tot_C;
int col[N], A[10005];
int pool[N << 1], *p = pool;
int *e[N], c[N];
const int limit = 16;
int L[N], R[N], bel[N];
int fa[N], val[N], siz[N];
Finline int find(int x) {
	while (x != fa[x]) x = fa[x];
	return x;
}
int res;
struct back_opt {
	int a, b;
} st[N << 1];
int top;
bool flag;
struct hash_table {
	std::unordered_set<int> S;
	int a[limit], cnt;
	bool fl;
	Finline void clear() {
		S.clear();
		fl = false;
		cnt = 0;
		memset(a, 0, sizeof(a));
	}
	Finline int size() { return cnt; }
	void upd(int x) {
		if (fl) {
			auto it = S.find(x);
			if (it == S.end())
				S.insert(x), ++cnt;
			else
				S.erase(it), --cnt;
		} else {
			for (int i = 0; i < limit; ++i)
				if (a[i] == x) {
					a[i] = 0;
					--cnt;
					return;
				}
			for (int i = 0; i < limit; i++)
				if (a[i] == 0) {
					a[i] = x;
					++cnt;
					return;
				}
			++cnt;
			fl = true;
			S.insert(x);
			for (int i = 0; i < limit; ++i) S.insert(a[i]);
		}
	}
} S[N];
int merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return 0;
	if (siz[x] > siz[y]) std::swap(x, y);
	fa[x] = y, siz[y] += siz[x];
	flag && ((st[++top] = (back_opt){x, y}), 0);
	res -= A[SZ(S[x])] + A[SZ(S[y])];
	if (S[x].fl) {
		for (auto _ : S[x].S) S[y].upd(_);
	} else {
		for (int i = 0; i < limit; ++i)
			if (S[x].a[i]) S[y].upd(S[x].a[i]);
	}
	res += A[SZ(S[y])];
	return siz[x];
	//	return SZ(S[x]);
}
void build() {
	for (int i = 1; i <= n; ++i) fa[i] = i, S[i].clear(), S[i].upd(col[i]), siz[i] = 1;
	for (int i = n; i >= 1; --i) {
		for (int _ = 0; _ < c[i]; ++_) {
			++val[i];
			int v = e[i][_];
			if (v > i) val[i] += merge(find(i), find(v));
		}
	}
	int tot = 0;
	for (int i = 1; i <= n; ++i) tot += val[i];
	int cur = 0;
	for (int i = 1; i <= n; ++i) {
		++cur;
		if (val[i] >= block_val) {
			L[cur] = i, R[cur] = i;
			bel[i] = cur;
			continue;
		}
		int j = i, sum = val[i];
		while (j < n && sum + val[j + 1] <= block_val) sum += val[++j];
		L[cur] = i, R[cur] = j;
		for (int k = i; k <= j; ++k) bel[k] = cur;
		i = j;
	}
}
int ans[N];
struct qry {
	int l, r, id;
	Finline bool operator<(const qry& o) const { return bel[l] == bel[o.l] ? r < o.r : bel[l] < bel[o.l]; }
} q[N];
int brute(int l, int r) {
	res = 0;
	for (int i = l; i <= r; ++i) fa[i] = i, S[i].clear(), S[i].upd(col[i]), res += A[1], siz[i] = 1;
	for (int i = r; i >= l; --i) {
		for (int _ = 0; _ < c[i]; ++_) {
			int v = e[i][_];
			if (v > i && v <= r) merge(i, v);
		}
	}
	return res;
}
int E[N][2];
int main() {
	read(n, m, tot_C);
	for (int i = 1; i <= n; ++i) read(col[i]);
	int x, y;
	for (int i = 1; i < n; ++i) read(x, y), E[i][0] = x, E[i][1] = y, ++c[x], ++c[y];
	for (int i = 1; i <= n; ++i) e[i] = p, p += c[i], c[i] = 0;
	for (int i = 1; i < n; ++i) x = E[i][0], y = E[i][1], e[x][c[x]++] = y, e[y][c[y]++] = x;
	for (int i = 0; i <= tot_C; ++i) read(A[i]);
	build();
	int _ = 0;
	for (int i = 1; i <= m; ++i) {
		read(x, y);
		if (bel[x] == bel[y])
			ans[i] = brute(x, y);
		else
			q[++_] = (qry){x, y, i};
	}
	std::sort(q + 1, q + _ + 1);
	for (int i = 1; i <= _; ++i) {
		res = 0;
		int j = i;
		while (j < _ && bel[q[j + 1].l] == bel[q[i].l]) ++j;
		int pos = R[bel[q[i].l]];
		int origL = pos;
		for (int k = L[bel[q[i].l]]; k <= n; ++k) fa[k] = k, S[k].clear(), S[k].upd(col[k]), siz[k] = 1;
		for (int k = i; k <= j; ++k) {
			top = 0, flag = false;
			while (pos < q[k].r) {
				++pos;
				res += A[SZ(S[pos])];
				for (int _ = 0; _ < c[pos]; ++_) {
					int v = e[pos][_];
					if (v > origL && v < pos) merge(pos, v);
				}
			}
			flag = true;
			int orig_res = res;
			int L = origL + 1;
			while (L > q[k].l) {
				--L;
				res += A[SZ(S[L])];
				for (int _ = 0; _ < c[L]; ++_) {
					int v = e[L][_];
					if (v <= pos && v > L) merge(L, v);
				}
			}
			ans[q[k].id] = res;
			while (top) {
				back_opt tmp(st[top--]);
				int x = tmp.a, y = tmp.b;
				siz[y] -= siz[x];
				fa[x] = x;
				if (S[x].fl) {
					for (auto _ : S[x].S) S[y].upd(_);
				} else {
					for (int i = 0; i < limit; ++i)
						if (S[x].a[i]) S[y].upd(S[x].a[i]);
				}
			}
			res = orig_res;
		}
		i = j;
	}
	for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}