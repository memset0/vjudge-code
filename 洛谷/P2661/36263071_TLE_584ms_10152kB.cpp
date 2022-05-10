//一般模拟 70分TLE 

#include <bits/stdc++.h> 
using namespace std;
const int maxn = 200010;
int n, ans, a[maxn], val[maxn], pos[maxn];
int main() {
	memset(val, 0, sizeof(val));
	cin >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	ans = n + 1;
	int i, j, k;
	for (i = 1; i <= n; i++) {
//		if (val[i]) continue;
		memset(pos, 0, sizeof(pos));
		k = pos[i] = 1;
		for (j = a[i]; true; j = a[j]) {
//			cout << "i = " << i << " j = " << j << " k = " << k << endl;
//			for (int i = 1; i <= n; i++)
//				printf("%d ", pos[i]);
//			puts("");
//			for (int i = 1; i <= n; i++)
//				printf("%d ", val[i]);
//			puts("");
//			puts("");
			k++;
			if (pos[j]) {
				if (pos[j] == -1) break;
				val[j] = k - pos[j];
				pos[j] = -1;
			} else {
				pos[j] = k;
			}
		}
	}
	for (int i = 1; i <= n; i++)
		if (val[i] != 0 && val[i] < ans) ans = val[i];
	cout << ans << endl;
	return 0;
}
