#include <bits/stdc++.h> 
using namespace std;
const int maxn = 40;
const int maxm = 20010;
int n, m, a[maxn], f[maxm];
int main() {
	cin >> m >> n;
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	f[0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = m; j >= a[i]; j--)	
			if (f[j - a[i]]) f[j] = 1;
	for (int i = m; i >= 0; i--)
		if (f[i]) {
			cout << m - i << endl;
			return 0;
		}
	return 0;
}