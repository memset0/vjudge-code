#include <bits/stdc++.h>
#define ll long long
using namespace std;
int read() {
	int x = 0; bool m = 0; char c = getchar();
	while (!isdigit(c) && c != '-') c = getchar();
	if (c == '-') m = 1, c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (m) return -x; else return x;
}
const int maxn = 10010, maxm = 100010;
int n, m, u, v, l, r, ans, q[maxn];
bool dis[maxn], val[maxn];
vector < int > g[maxn];
int main() {
	n = read(), m = read();
	for (int i = 1; i <= m; i++) {
		u = read(), v = read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	l = r = q[1] = dis[1] = val[1] = ans = 1;
	while (l <= r && ans != -1) {
		u = q[l++];
		for (vector < int > ::iterator it = g[u].begin(); it != g[u].end(); it++) {
			if (!dis[*it]) {
				dis[*it] = 1;
				val[*it] = val[u] ^ 1;
				q[++r] = *it;
			} else {
//				cout << '!'; 
				if (val[*it] != (val[u] ^ 1)) {
					ans = -1;
					break;
				}
			}
		}
	}
//	for (int i = 1; i <= n; i++)
//		cout << dis[i] << " ";
//	cout << endl;
//	for (int i = 1; i <= n; i++)
//		cout << val[i] << " ";
//	cout << endl;
	if (ans == -1) printf("Impossible\n");
	else printf("%d\n", min(ans, n - ans));
	return 0;
}