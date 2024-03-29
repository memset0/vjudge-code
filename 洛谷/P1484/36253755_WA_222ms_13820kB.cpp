// luogu-judger-enable-o2
// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define rep(i,l,r) for (int i = l; i <= r; i++)
#define getc(x) getchar(x)
#define putc(x) putchar(x)

template <typename T> inline void read(T &x) {
	x = 0; register char ch; register bool fl = 0;
	while (ch = getc(), ch < 48 || 57 < ch) fl ^= ch == '-'; x = (ch & 15);
	while (ch = getc(), 47 < ch && ch < 58) x = (x << 1) + (x << 3) + (ch & 15);
	if (fl) x = -x;
}
template <typename T> inline void readc(T &x) {
	while (x = getc(), !islower(x) && !isupper(x));
}
template <typename T> inline void print(T x, char c = ' ') {
	static int buf[40];
	if (x == 0) { putc('0'); putc(c); return; }
	if (x < 0) putc('-'), x = -x;
	for (buf[0] = 0; x; x /= 10) buf[++buf[0]] = x % 10 + 48;
	while (buf[0]) putc((char) buf[buf[0]--]);
	putc(c);
}

const int maxn = 1000010;
int n, m, pos, l[maxn], r[maxn];
ll sum, ans, val[maxn];
bool vis[maxn];

struct node {
	int id;
	ll val;
} u, v;
bool operator < (const node &a, const node &b) {
	return a.val < b.val;
}
std::priority_queue < node > q;

int main() {
	// freopen("1.in", "r", stdin);
	read(n), read(m);
	for (int i = 1; i <= n; i++)
		read(val[i]);
	for (int i = 1; i <= n; i++)
		l[i] = i - 1, r[i] = i + 1;
	pos = n;
	for (int i = 1; i <= n; i++)
		q.push(node{i, val[i]});
	val[0] = val[n + 1] = -1e9;
	for (int i = 1; i <= m; i++) {
		while (vis[q.top().id])	
			q.pop();
		u = q.top(), q.pop();
		// printf(">> %d %d\n", u.id, u.val);
		vis[u.id] = vis[l[u.id]] = vis[r[u.id]] = 1;
		sum += u.val, ans = std::max(ans, sum);
		v.id = ++pos;
		l[v.id] = l[l[u.id]];
		r[v.id] = r[r[u.id]];
		r[l[u.id]] = v.id;
		l[r[u.id]] = v.id;
		v.val = val[l[u.id]] + val[r[u.id]] - val[u.id];
		q.push(v);
	}
	print(ans, '\n');
	return 0;
}
