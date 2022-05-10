// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.01.11 18:20:48
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, l, r) for (register int i = l; i <= r; i++)

namespace ringo {
typedef long long ll;
typedef unsigned long long ull;

inline char read() {
	static const int IN_LEN = 1000000; static char buf[IN_LEN], *s, *t;
	return (s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin), (s == t ? -1 : *s++) : *s++);
}
template <class T> inline void read(T &x) {
	static bool f; static char c;
	for (f = 0, c = read(); !isdigit(c); c = read()) { f ^= c == '-'; if (c == -1) return; }
	for (x = 0; isdigit(c); c = read()) x = ((x + (x << 2)) << 1) + (c ^ '0');
	if (f) x = -x;
}
const int OUT_LEN = 10000000; char obuf[OUT_LEN], *ooh = obuf;
inline void print(char c) {
	if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
	*ooh++ = c;
}
template<class T> inline void print(T x) {
	static int buf[30], cnt;
	if (!x) { print('0'); return; }
	if (x < 0) print('-'), x = -x;
	for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + '0';
	while (cnt) print((char)buf[cnt--]);
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), print(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const size_t N = 1010;
int n, m, q, t, limit[N];
bool vis[N];
std::bitset <N> ans, bit[N][N];
std::vector <int> now[2], G[N];

void main() {
	read(n), read(m), read(q);
	for (register int i = 1, u, v; i <= m; ++i) {
		read(u), read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (register int s = 1; s <= n; ++s) {
		memset(vis, 0, sizeof(vis));
		bit[s][0].set(s), now[1].push_back(s), vis[s] = 1;
		for (register int i = 1; now[i & 1].size(); ++i) {
			bit[s][i] = bit[s][i - 1];
			for (auto u : now[i & 1])
				for (auto v : G[u])
					if (!vis[v]) {
						vis[v] = 1, bit[s][i].set(v);
						now[i & 1 ^ 1].push_back(v);
					}
			now[i & 1].clear(), limit[s] = i;
		}
	}
	for (int i = 1, x, y; i <= q; i++) {
		ans.reset();
		for (read(t); t--; ) {
			read(x), read(y);
			ans |= bit[x][std::min(y, limit[x])];
		}
		print(ans.count(), '\n');
	}
}

} signed main() { return ringo::main(), ringo::flush(), 0; }