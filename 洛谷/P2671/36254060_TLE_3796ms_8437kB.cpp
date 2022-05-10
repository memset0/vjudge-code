#include <bits/stdc++.h>
#define isNum(c) ('0'<=c&&c<='9')
using namespace std;
const int maxn = 100010;
int n, m, a[maxn], c[maxn];
vector < int > v[maxn][2];
int read() {
	char c = getchar();
	while (!isNum(c)) c = getchar();
	int ret = 0;
	while (isNum(c)) {
		ret = ret * 10 + c - '0';
		c = getchar();
	}
	return ret;
}
int ans = 0;
int main() {
//	freopen("1.in", "r", stdin);
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		a[i] = (read() % 10007);
	for (int i = 1; i <= n; i++)
		c[i] = read();
	for (int i = 1; i <= n; i++)
		v[c[i]][i%2].push_back(i);
	for (int t = 1; t <= m; t++) {
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < v[t][k].size(); i++) {
				for (int j = i + 1; j < v[t][k].size(); j++) {
						ans = (ans + ((v[t][k][i] + v[t][k][j]) % 10007) * (a[v[t][k][i]] + a[v[t][k][j]])) % 10007;
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}