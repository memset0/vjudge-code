// =================================
//   author: memset0
//   date: 2019.02.26 14:23:10
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

const int N = 3e5 + 10, mod1 = 998244353, mod2 = 1e9 + 7;
int n, m;
int a[N];

inline int dec(int a, int b, int p) { a -= b; return a < 0 ? a + p : a; }
inline int sub(int a, int b, int p) { a += b; return a >= p ? a - p : a; }
inline int mul(int a, int b, int p) { return (ll)a * b - (ll)a * b / p * p; }

struct hash {
	int a, b;
	inline hash() {}
	inline hash(int x) { a = b = x; }
	inline hash(int x, int y) { a = x, b = y; }
	friend inline hash operator + (const hash &a, const hash &b) { return hash(sub(a.a, b.a, mod1), sub(a.b, b.b, mod2)); }
	friend inline hash operator - (const hash &a, const hash &b) { return hash(dec(a.a, b.a, mod1), dec(a.b, b.b, mod2)); }
	friend inline hash operator * (const hash &a, const hash &b) { return hash(mul(a.a, b.a, mod1), mul(a.b, b.b, mod2)); }
	friend inline bool operator == (const hash &a, const hash &b) { return a.a == b.a && a.b == b.b; }
} L, R, pow[N];

struct node {
	int l, r, mid, siz;
	hash lsh, rsh;
} p[N << 2];

inline void maintain(int u) {
	p[u].lsh = p[u << 1].lsh * pow[p[u << 1 | 1].siz] + p[u << 1 | 1].lsh;
	p[u].rsh = p[u << 1].rsh + p[u << 1 | 1].rsh * pow[p[u << 1].siz];
}

void build(int u, int l, int r) {
	p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1, p[u].siz = r - l + 1;
	if (l == r) { p[u].lsh = p[u].rsh = 0; return; }
	build(u << 1, l, p[u].mid), build(u << 1 | 1, p[u].mid + 1, r);
	maintain(u);
}

void modify(int u, int k) {
	if (p[u].l == p[u].r) { p[u].lsh = p[u].rsh = 1; return; }
	modify(k <= p[u].mid ? u << 1 : u << 1 | 1, k);
	maintain(u);
}

int query(int u, int k) {
	if (p[u].l == p[u].r) return p[u].lsh.a;
	return query(k <= p[u].mid ? u << 1 : u << 1 | 1, k);
}

#define LSH 0
#define RSH 1
hash query(int u, int l, int r, bool flag) {
	// printf("query %d[%d %d] %d %d %d => [%d %d %d %d]\n", u, p[u].l, p[u].r, l, r, flag, p[u].lsh.a, p[u].lsh.b, p[u].rsh.a, p[u].rsh.b);
	if (l == p[u].l && r == p[u].r) return flag == LSH ? p[u].lsh : p[u].rsh;
	if (r <= p[u].mid) return query(u << 1, l, r, flag);
	if (l > p[u].mid) return query(u << 1 | 1, l, r, flag);
	return flag == LSH ? query(u << 1, l, p[u].mid, flag) * pow[r - p[u].mid] + query(u << 1 | 1, p[u].mid + 1, r, flag) :
		query(u << 1, l, p[u].mid, flag) + query(u << 1 | 1, p[u].mid + 1, r, flag) * pow[p[u].mid - l + 1];
}

void main() {
	read(n), pow[0] = 1, build(1, 1, n);
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * hash(131);
	// printf(">>> %d %d : %d %d : %d %d\n", pow[0].a, pow[0].b, hash(131).a, hash(131).b, (pow[0] * hash(131)).a, (pow[0] * hash(131)).b);
	// for (int i = 0; i <= n; i++) printf("[%d %d]%c", pow[i].a, pow[i].b, " \n"[i == n]);
	// printf(">>> %d %d\n", mul(1, 131, mod1), mul(1, 131, mod2));
	for (int i = 1, len; i <= n; i++) {
		// printf(">>> [%d] => %d\n", i, a[i]);
		len = std::min(a[i] - 1, n - a[i]);
		if (len) {
			// printf("[%d %d] [%d %d]\n", a[i] - len, a[i] - 1, a[i] + 1, a[i] + len);
			L = query(1, a[i] - len, a[i] - 1, LSH);
			R = query(1, a[i] + 1, a[i] + len, RSH);
			// for (int j = a[i] - len; j <= a[i] - 1; j++) print(query(1, j), ' '); puts("");
			// for (int j = a[i] + 1; j <= a[i] + len; j++) print(query(1, j), ' '); puts("");
			// printf("[%d %d] [%d %d]\n", L.a, L.b, R.a, R.b);
			if (!(L == R)) { puts("YES"); return; }
		}
		modify(1, a[i]);
		// printf(">>>>> "); for (int i = 1; i <= n; i++) print(query(1, i), " \n"[i == n]);
	} puts("NO");
}

} signed main() { return ringo::main(), 0; }