#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll read() {
	ll x = 0; bool m = 0; char c = getchar();
	while (!isdigit(c) && c != '-') c = getchar();
	if (c == '-') c = getchar(), m = 1;
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (m) return -x; else return x;
}
const int maxn = 1010;
ll n, x, y, sum;
double ans;
struct Node {
	ll a, b, times;
} a[maxn];
bool cmp(Node a, Node b) {
	return a.times < b.times;
}
int main() {
	n = read(), x = read(), y = read();
	for (int i = 1; i <= n; i++)
		a[i].a = read(), a[i].b = read(), a[i].times = a[i].a * a[i].b;
	sort(a + 1, a + n + 1, cmp);
	sum = a[0].a = 1;
	for (int i = 1; i <= n; i++) {
		sum *= a[i - 1].a;
		ans = max(ans, sum / (double)a[i].b);
	}
	printf("%.0lf\n", floor(ans));
	return 0;
}