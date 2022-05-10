#include <bits/stdc++.h> 
#define isNum(c) ('0'<=c&&c<='9')
#define dist(i, j) (sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])+(z[i]-z[j])*(z[i]-z[j])))
using namespace std;
const int maxn = 1010;
int t, n, h, r, x[maxn], y[maxn], z[maxn], fa[maxn];
bool mark, dis[maxn];
char c; int ret;
int read() {
	c = getchar();
	while (!isNum(c)) c = getchar();
	ret = 0;
	while (isNum(c)) {
		ret = ret * 10 + c - '0';
		c = getchar();
	}
	return ret;
}
int find(int x) {
	if (fa[x] == x) return x;
	else return fa[x] = find(fa[x]);
}
int main() {
	t = read();
	while (t--) {
		n = read(); h = read(); r = read();
		for (int i = 1; i <= n; i++)
			fa[i] = i; //初始化并查集 
		memset(dis, 0, sizeof(dis)) ;
		for (int i = 1; i <= n; i++) {
			x[i] = read(); y[i] = read(); z[i] = read();
		}
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++)
				if (dist(i, j) <= 2 * r)
					fa[find(i)] = find(j); //合并
		for (int i = 1; i <= n; i++)
			if (z[i] <= r)
				dis[find(i)] = 1;
		mark = false;
		for (int i = 1; i <= n; i++)
			if (z[i] + r >= h)
				if (dis[find(i)]) {
					mark = true;
					break;
				}
		if (mark) puts("YES");
		else puts("NO");
	}
	return 0;
}
	