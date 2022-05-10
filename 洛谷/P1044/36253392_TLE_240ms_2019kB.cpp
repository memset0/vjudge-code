#include <bits/stdc++.h>
using namespace std;
const int maxn = 20;
int n;
long long ans = 0;
void DFS(int i, int k) {
	if (i <= n)
		DFS(i + 1, k + 1);
	if (k > 0) 
		DFS(i, k - 1);
	if (i > n && k <= 0) {
		ans++;
		return ;
	}
}
int main() {
	cin >> n;
	DFS(1, 0);
	cout << ans << endl;
	return 0;
}