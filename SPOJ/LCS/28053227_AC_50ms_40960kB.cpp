// =================================
//   author: memset0
//   date: 2019.01.17 19:26:39
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

const int N = 5e5 + 10;
int n, m, lst = 1, cnt = 1, clen, ans, length;
int len[N], ch[N][26], fa[N];
char a[N], b[N];

void insert(int c) {
	int f = lst, u = ++cnt; len[lst = u] = ++clen;
	while (f && !ch[f][c]) ch[f][c] = u, f = fa[f];
	if (!f) return (void)(fa[u] = 1);
	int s = ch[f][c];
	if (len[s] == len[f] + 1) return (void)(fa[u] = s);
	int p = ++cnt; len[p] = len[f] + 1, fa[p] = fa[s], fa[s] = fa[u] = p;
	for (register int i = 0; i < 26; i++) ch[p][i] = ch[s][i];
	while (f && ch[f][c] == s) ch[f][c] = p, f = fa[f];
}

void main() {
	scanf("%s%s", a + 1, b + 1), n = strlen(a + 1), m = strlen(b + 1);
	for (int i = 1; i <= n; i++) insert(a[i] - 'a');
	// for (int i = 1; i <= n; i++) putchar(a[i]), putchar(" \n"[i == n]);
	// for (int i = 1; i <= m; i++) putchar(b[i]), putchar(" \n"[i == m]);
	// for (int i = 1; i <= cnt; i++) print(fa[i], " \n"[i == cnt]);
	// for (int i = 1; i <= cnt; i++) print(len[i], " \n"[i == cnt]);
	// for (int k = 0; k < 26; k++)
	// 	for (int i = 1; i <= cnt; i++)
	// 		print(ch[i][k], " \n"[i == cnt]);
	for (int i = 1, p = 1, c; i <= m; i++) {
		c = b[i] - 'a';
		while (p && !ch[p][c]) p = fa[p];
		// printf(">>> %d %d\n", p, length);
		if (!p) p = 1, length = 0;
		else {
			length = std::min(length, len[p]) + 1;
			p = ch[p][c];
		} ans = std::max(ans, length);
	} print(ans, '\n');
}

} signed main() { return ringo::main(), 0; }