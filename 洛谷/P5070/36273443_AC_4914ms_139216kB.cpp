// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2019.03.06 23:20:58
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

const int N = 1e6 + 20;
int n, m, a[N], tag[N], lst[N], s[11][N], ans[N][11];
std::vector <std::pair <int, int> > vet, qry[N];

void modify(int k, int w, int u) { for (int i = k; i; i -= i & -i) s[u][i] += w; }
void query(int k, int *ans) {
	for (int i = k; i <= n; i += i & -i)
		for (int u = 1; u <= 10; u++) ans[u] += s[u][i];
}

void main() {
	read(n), read(m);
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = 1, l, r; i <= m; i++) read(l), read(r), qry[r].push_back(std::make_pair(l, i));
	for (int u = 1; u <= n; u++) {
		vet.clear();
		for (int i = std::max(1, a[u] - 11); i <= a[u] + 11; i++)
			if (lst[i] && lst[i] > lst[a[u]]) vet.push_back(std::make_pair(lst[i], i));
		vet.push_back(std::make_pair(lst[a[u]], -1));
		vet.push_back(std::make_pair(u, a[u]));
		std::sort(vet.rbegin(), vet.rend());
		tag[a[u]] = 1;
		for (int i = 0; i < vet.size() - 1; i++) {
			int L = 0, R = 0; if (~vet[i].second) tag[vet[i].second] = 1;
			while (tag[a[u] - L - 1]) ++L;
			while (tag[a[u] + R + 1]) ++R;
			int U = L + R + 1;
			if (1 <= L && L <= 10) modify(vet[i].first, -1, L), modify(vet[i + 1].first,  1, L);
			if (1 <= R && R <= 10) modify(vet[i].first, -1, R), modify(vet[i + 1].first,  1, R);
			if (1 <= U && U <= 10) modify(vet[i].first,  1, U), modify(vet[i + 1].first, -1, U);
		}
		tag[a[u]] = 0;
		for (auto it = vet.begin(); it != vet.end(); it++) if (~it->second) tag[it->second] = 0;
		for (auto it = qry[u].begin(); it != qry[u].end(); it++) query(it->first, ans[it->second]);
		lst[a[u]] = u;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= 10; j++) print(ans[i][j] % 10);
		putchar('\n');
	}
}

} signed main() { return ringo::main(), 0; }