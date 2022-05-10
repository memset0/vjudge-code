#include <bits/stdc++.h> 
using namespace std;
const int maxn = 200010;
int n, ans, a[maxn], val[maxn], pos[maxn];
int main() {
	memset(val, -1, sizeof(val));
	cin >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	ans = n + 1;
	int i, j, k;
	for (i = 1; i <= n; i++) {
		memset(pos, 0, sizeof(pos));
		k = pos[i] = 1;
		for (j = a[i]; !pos[j] && k <= ans; j = a[j]) {
			pos[j] = 1;
			k++;
		}
		if (i == j) {
			for (int t = 1; t <= n; t++)
				if (pos[i]) val[i] = k;
			ans = min(ans, k);
		}
	}
	cout << ans << endl;
	return 0;
}