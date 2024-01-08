#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair <int, int> pii;


vector <int> solve (int w) {
	if (w == 1) return {0, 1};
	auto a = solve(w - 1);
	auto b = a;
	reverse(b.begin(), b.end());
	for (auto i : b) a.push_back(i | (1 << (w - 1)));
	return a;
}
int n;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
	int w = 1;
	while ((1 << w) <= n) w ++;
	auto W = solve(w);
	for (int i = 1; i < W.size(); i += 2) W[i] ^= (1 << w) - 1; 
	for (int i = 1; i < W.size(); i++) {
		int b = W[i] & W[i - 1];
		if (b) {
			assert (__builtin_popcount(b) == 1);
			W[i] ^= b;
		}
	}
	cout << "Yes" << endl;
	int a[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = ((W[(i + j) % (1 << w)] << w) | W[(i + j % 2) % (1 << w)]);
			cout << a[i][j] << (j == n - 1 ? '\n' : ' ');
		}
	}
	vector <int> cnt (4 * n * n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			assert (0 <= a[i][j] && a[i][j] < 4 * n * n);
			assert (++cnt[a[i][j]] <= 4);
			assert (!i || ((a[i][j] & a[i - 1][j]) == 0));
			assert (!j || ((a[i][j] & a[i][j - 1]) == 0));
		}
	}
}