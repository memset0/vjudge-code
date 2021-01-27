// =================================
//   author: memset0
//   date: 2019.07.19 16:07:04
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define rep(i, l, r) for (int i = (l), i##ed = (r); i <= i##ed; ++i)
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
template <class T> inline void print(T a, int l, int r, std::string s = "") {
	if (s != "") std::cout << s << ": ";
	for (int i = l; i <= r; i++) print(a[i], " \n"[i == r]);
}

const int N = 1e5 + 10;
int id, n, m, fa[N], ch[N][2];
std::vector<std::tuple<int, int, int>> set;
int val[N], sum[N], rev[N], vir[N];

namespace lct {
	inline bool getson(int x) { return ch[fa[x]][1] == x; }
	inline bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
	inline void pushdown(int);
	inline void pushup(int x) { rev[x] ^= 1; }
	inline void pushdown(int x) { if (rev[x]) rev[x] = 0, rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1, std::swap(ch[x][0], ch[x][1]); }
	inline void maintain(int x) { sum[x] = sum[ch[x][0]] ^ val[x] ^ vir[x] ^ sum[ch[x][1]]; }
	void rotate(int x) {
		if (!x || !fa[x]) return;
		int f = fa[x], ff = fa[f], fs = getson(x), ffs = getson(f), y = ch[x][fs ^ 1];
		if (!isroot(f)) ch[ff][ffs] = x; ch[x][fs ^ 1] = f, ch[f][fs] = y;
		fa[y] = f, fa[f] = x, fa[x] = ff, maintain(f), maintain(x);
	} 
	void clear(int x) { if (!isroot(x)) clear(fa[x]); pushdown(x); }
	void splay(int x) { clear(x); for (; !isroot(x); rotate(x)) if (!isroot(fa[x])) rotate(getson(x) == getson(fa[x]) ? fa[x] : x); }
	void access(int x) { for (int y = 0; x; y = x, x = fa[x]) splay(x), vir[x] ^= sum[y] ^ sum[ch[x][1]], ch[x][1] = y, maintain(x); }
	void mroot(int x) { access(x), splay(x), pushup(x); }
	void split(int x, int y) { mroot(x), access(y), splay(y); }
	void setup(int x, int v) { mroot(x), val[x] ^= v, maintain(x); }
	void link(int x, int y) { mroot(x), mroot(y), fa[x] = y, vir[y] ^= sum[x]; }
	void cut(int x, int y) { split(x, y), fa[x] = ch[y][0] = 0, maintain(y); }
	inline bool check_edge(int x, int y) { split(x, y); return fa[x] == y && ch[y][0] == x; }
} using namespace lct;

void main() {
	srand(20040725);
	read(id), read(n), read(m);
	for (int i  = 1, x, y; i < n; i++) {
		read(x), read(y);
		mroot(x), fa[x] = y;
	}
	for (int i = 1, x, y, z, k, op, all = 0; i <= m; i++) {
		read(op);
		if (op == 1) {
			read(x), read(y), cut(x, y);
			// fprintf(stderr, "[%d] >> 1 : cut %d %d\n", i, x, y);
			read(x), read(y), link(x, y);
			// fprintf(stderr, "[%d] >> 1 : link %d %d\n", i, x, y);
		} else if (op == 2) {
			read(x), read(y), z = rand();
			setup(x, z), setup(y, z), all ^= z;
			set.push_back(std::make_tuple(x, y, z));
			// fprintf(stderr, "[%d] >> 2 : %d %d %d %d\n", i, x, y, z, (int)set.size());
		} else if (op == 3) {
			read(k); const auto &it = set[k - 1];
			x = std::get<0>(it), y = std::get<1>(it), z = std::get<2>(it);
			setup(x, z), setup(y, z), all ^= z;
			// fprintf(stderr, "[%d] >> 3 : %d %d %d %d\n", i, x, y, z, k);
		} else {
			read(x), read(y);
			split(x, y), puts(all == sum[x] ? "YES" : "NO");
			// fprintf(stderr, "[%d] >> 4 : %d %d : %d %d\n", i, x, y, all, sum[y]);
		}
		// for (int i = 1; i <= n; i++)
		//   printf("%d : fa=%d lc=%d rc=%d | val=%d sum=%d vir=%d\n", i, fa[i], ch[i][0], ch[i][1], val[i], sum[i], vir[N]);
		// for (int i = 1; i <= n; i++)
		//   for (int j = i + 1; j <= n; j++)
		//     if (check_edge(i, j))
		//       printf("%d %d\n", i, j);
	}
}

} signed main() {
#ifdef memset0
	freopen("1.in", "r", stdin);
#endif
	return ringo::main(), 0;
}