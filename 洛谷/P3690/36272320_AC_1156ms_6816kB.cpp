// =================================
//   author: memset0
//   date: 2019.01.21 12:04:40
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
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

const int N = 3e5 + 10;
int n, m;
int fa[N], ch[N][2], sum[N], val[N];
bool rev[N];

inline bool getSon(int x) { return ch[fa[x]][1] == x; }
inline bool isRoot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
inline void update(int x) { sum[x] = sum[ch[x][0]] ^ val[x] ^ sum[ch[x][1]]; }
inline void rotate(int x) {
	if (!x || !fa[x]) return;
	int f = fa[x], fs = getSon(x), ff = fa[f], ffs = getSon(f), y = ch[x][fs ^ 1];
	if (!isRoot(f)) ch[ff][ffs] = x; ch[x][fs ^ 1] = f, ch[f][fs] = y;
	fa[y] = f, fa[f] = x, fa[x] = ff, update(f), update(x);
}
void cleanUp(int x) {
	if (!isRoot(x)) cleanUp(fa[x]);
	if (rev[x]) std::swap(ch[x][0], ch[x][1]), rev[ch[x][0]] ^= 1, rev[ch[x][1]] ^= 1, rev[x] = 0;
}
inline void splay(int x) {
	cleanUp(x);
	for (int f = fa[x]; !isRoot(x); rotate(x), f = fa[x])
		if (!isRoot(f)) rotate(getSon(f) == getSon(x) ? f : x);
}
inline void access(int x) { for (int y = 0; x; y = x, x = fa[x]) splay(x), ch[x][1] = y, update(x); }
inline void makeRoot(int x) { access(x), splay(x), rev[x] ^= 1; }
inline int getRoot(int x) { access(x), splay(x); while(ch[x][0]) x = ch[x][0]; return x; }
inline void split(int x, int y) { makeRoot(x), access(y), splay(y); }
inline void link(int x, int y) { if (getRoot(x) != getRoot(y)) makeRoot(x), fa[x] = y, update(y); }
inline void cut(int x, int y) { if (getRoot(x) == getRoot(y)) { split(x, y); if (!ch[x][1] && fa[x] == y && ch[y][0] == x) fa[x] = ch[y][0] = 0, update(y); }}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(val[i]), update(i);
	for (int i = 1, x, y, op; i <= m; i++) {
		read(op), read(x), read(y);
		if (!op) split(x, y), print(sum[y], '\n');
		else if (op == 1) link(x, y);
		else if (op == 2) cut(x, y);
		else makeRoot(x), val[x] = y, update(x);
	}
}

} signed main() { return ringo::main(), 0; }