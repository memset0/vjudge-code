// =================================
//   author: memset0
//   date: 2019.01.12 13:44:20
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

const int N = 1e5 + 10;
int T, n, m, ans, cnt;
int rt[N], l[N], r[N], id[N], val[N], ch[N][2], dis[N], pos[N];

inline int new_node(int w, int i) { val[i] = w, dis[i] = 1; return id[i] = i; }

inline int merge(int x, int y) {
	if (!x || !y) return x | y;
	if (val[x] > val[y] || (val[x] == val[y] && id[x] > id[y])) std::swap(x, y);
	ch[x][1] = merge(ch[x][1], y);
	if (dis[ch[x][0]] < dis[ch[x][1]]) std::swap(ch[x][0], ch[x][1]);
	dis[x] = dis[ch[x][0]] + 1;
	return x;
}

void main() {
	for (read(T); T--; ) {
		read(n), cnt = 0;
		for (int i = 1; i <= n; i++) rt[i] = ch[i][0] = ch[i][1] = 0, pos[i] = i;
		for (int i = 1; i <= n; i++) {
			read(l[i]), read(r[i]);
			rt[l[i]] = merge(rt[l[i]], new_node(r[i], i));
		}
		ans = 1;
		for (int i = 1, nxt, x, y; i <= n; i++) {
			while (rt[i] && val[rt[i]] < i)
				rt[i] = merge(ch[rt[i]][0], ch[rt[i]][1]);
			if (rt[i]) {
				// std::cout << rt[i] << " " << val[rt[i]] << " " << id[rt[i]] << std::endl;
				if (id[rt[i]] != i) {
					// printf("%d %d : %d %d\n", rt[i], pos[i], id[rt[i]], id[pos[i]]);
					x = rt[i], y = pos[i];
					std::swap(id[x], id[y]);
					std::swap(pos[id[x]], pos[id[y]]);
					ans *= -1;
				}
				nxt = val[rt[i]];
				rt[i] = merge(ch[rt[i]][0], ch[rt[i]][1]);
				if (nxt + 1 <= n) {
					// printf("%d => %d\n", i, nxt + 1);
					rt[nxt + 1] = merge(rt[i], rt[nxt + 1]);
				}
			} else {
				ans = 0;
				break;
			}
		}
		// std::cout << ans << std::endl;
		putchar("FDY"[ans + 1]), putchar('\n');
	}
}

} signed main() { return ringo::main(), 0; }
