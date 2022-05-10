// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll read() {
    ll x = 0; bool m = 0; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') m = 1, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (m) return -x; else return x;
}

const int maxn = 50010;
int n, top, s[maxn];
ll ans;

struct node {
	ll x, y;
} a[maxn];

bool cmp(node fjk, node djx) {
	double A = atan2(fjk.y - a[1].y, fjk.x - a[1].x);
	double B = atan2(djx.y - a[1].y, djx.x - a[1].x);
	if (A == B) return fjk.x < djx.x;
	return A < B;
}

ll cross(node a, node b, node c) {
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

ll dis(node a, node b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
	// freopen("INPUT", "r", stdin);
	// freopen("OUTPUT", "w", stdout);

	n = read();
	for (int i = 1; i <= n; i++)
		a[i].x = read(), a[i].y = read();

	for (int i = 2; i <= n; i++)
		if (a[i].x < a[1].x || (a[i].x == a[1].x && a[i].y < a[1].y))
			swap(a[1], a[i]);
	sort(a + 2, a + n + 1, cmp);

	s[1] = 1, s[2] = 2, top = 2;
	for (int i = 3; i <= n; i++) {
		while (top >= 2 && cross(a[s[top - 1]], a[i], a[s[top]]) >= 0)
			top--;
		s[++top] = i;
	}

	// for (int i = 1; i <= top; i++)
	// 	for (int j = 1; j <= top; j++)
	// 		ans = max(ans, dis(a[s[i]], a[s[j]]));

	for (int i = 1, j = 3; i <= top; i++) {
		while (cross(a[s[i]], a[s[(i == top) ? 1 : (i + 1)]], a[s[j]]) > cross(a[s[i]], a[s[(i == top) ? 1 : (i + 1)]], a[(j == top) ? 1 : (j + 1)]))
			j = (j == top) ? 1 : (j + 1);
		// cout << i << " " << ((i == top) ? 1 : (i + 1)) << " " <<  j << " " << ((j == top) ? 1 : (j + 1)) << endl;
		ans = max(ans, max(dis(a[s[i]], a[s[j]]), dis(a[s[(i == top) ? 1 : (i + 1)]], a[s[j]])));
	}

	printf("%lld\n", ans);

	return 0;
}