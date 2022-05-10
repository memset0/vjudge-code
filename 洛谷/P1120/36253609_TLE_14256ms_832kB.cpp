// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
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

const int maxn = 70;
int n, t, x;
int siz, lim, sum;
int a[maxn], used[maxn];

bool cmp(int a, int b) {
	return a > b;
}

void dfs(int cnt, int sum, int cur) {
	if (sum == siz)
		cnt++, sum = 0, cur = 1;
	if (sum > siz)
		return;
//	printf("dfs %d %d %d\n", cnt, sum, cur);
	if (cnt == lim) {
		printf("%d\n", siz);
		exit(0);
	}
	for (int i = cur; i <= n; i++)
		if (!used[i] && a[i] + sum <= siz) {
			used[i] = 1;
			dfs(cnt, sum + a[i], i + 1);
			used[i] = 0;
		}
}

int main() {
	
	t = read();
	for (int i = 1; i <= t; i++) {
		x = read();
		if (x <= 50) a[++n] = x;
	}
	
	for (int i = 1; i <= n; i++)
		sum += a[i];
	sort(a + 1, a + n + 1, cmp);

	for (int i = n; i >= 1; i--)
		if (sum % i == 0) {
			lim = i, siz = sum / i;
			dfs(0, 0, 1);
		}
	
	return 0;
}