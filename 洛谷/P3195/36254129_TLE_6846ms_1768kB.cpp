// luogu-judger-enable-o2
// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
#define sqr(x) ((x)*(x))
using namespace std;

int read() {
    int x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}

const int maxn = 50010;
int n;
ll l, a[maxn], s[maxn], f[maxn];

int main() {
	// freopen("INPUT", "r", stdin);
	// freopen("OUTPUT", "w", stdout);

	n = read(), l = read();
	for (int i = 1; i <= n; i++)
		a[i] = read(), s[i] = s[i - 1] + a[i];

	for (int i = 1; i <= n; i++) {
		f[i] = 0x7fffffffffffffff;
		for (int j = 0; j < i; j++) {
			f[i] = min(f[i], f[j] + sqr(s[i] + i - s[j] - j - 1 - l));
		}
		// printf("%lld\n", f[i]);
	}
	printf("%lld\n", f[n]);

	return 0;
}