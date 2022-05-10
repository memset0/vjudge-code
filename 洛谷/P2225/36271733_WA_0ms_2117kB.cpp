#include <bits/stdc++.h>
using namespace std;
const int maxn = 40;
int n, f[maxn];
int main() {
	cin >> n;
	f[0] = 1;
	for (int i = 1; i <= n; i++)
		f[i] = f[i - 1] + f[i - 2];
	cout << f[n];
	return 0;
}


//#include <bits/stdc++.h>
//using namespace std;
//const int maxn = 40;
//const int mov[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
//
//int n, i, j, x, y, t, tt, ttt, ans, sum, a[maxn][maxn], b[maxn][maxn], f[maxn * maxn];
//int main() {
//	for (n = 1; n <= 2; n++) {
//		memset(f, 0, sizeof(f));
//		ans = 0;
//		while (!f[n * n + 1]) {
//			for (i = 1; i <= n; i++)
//				for (j = 1; j <= n; j++)
//					a[i][j] = f[(i - 1) * n + j];
//			
//			for (int i = 1; i <= n; i++) {
//				for (int j = 1; j <= n; j++)
//					printf("%d ", a[i][j]);
//				puts("");
//			}
//			puts("");
//			
//			sum = 0;
//			for (i = 1; i <= n; i++) {
//				for (j = 1; j <= n; j++) {
//					tt = a[i][j];
//					for (t = 0; t < 4; t++) {
//						x = i + mov[t][0];
//						y = j + mov[t][1];
//						if (x > 0 && y > 0 && x <= n && y <= n) {
//							tt ^= a[x][y];
//						}
//					}
//					if (tt > a[i][j]) sum++;
//					else if (tt < a[i][j]) sum--;
//				}
//			}
//			if (!sum) ans++;
//			
//			f[1]++;
//			for (i = 1; i <= n * n; i++)
//				if (f[i] >> 1) {
//					f[i] = 0;
//					f[i + 1]++;
//				}
//		}
//		
//		printf("%d\n", ans);
//	}
//	return 0;
//}