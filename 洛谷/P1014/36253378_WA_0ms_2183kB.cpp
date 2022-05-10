#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, m;
	cin >> n;
	for (m = 1; n > m; n -= m, m++);
	printf("%d/%d\n", n, m + 1 - n);
	return 0;
}