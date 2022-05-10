#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;
const int maxm = 10000010;
int n, m, a[maxn], f[maxm];
int main() {
	cin >> m >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	f[0] = f[1] = 1;
	for (int i = 1; i <= m; i++)
		if (!f[i]) {
			for (int j = i * 2; j <= m; j += i)
				f[j] = 1;
		}
	for (int i  = 1; i <= n; i++)
		if (f[a[i]]) puts("No");
		else puts("Yes");
	return 0;
}