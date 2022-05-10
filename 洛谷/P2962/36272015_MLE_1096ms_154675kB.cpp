#include <bits/stdc++.h>
#define isnum(c) ('0' <= c && c <= '9')
#define read(x) do {\
	R::c = getchar(); R::m = 0; x = 0;\
	while (!isnum(R::c) && R::c != '-') R::c = getchar();\
	if (R::c == '-') R::c = getchar(), R::m = 1;\
	while (isnum(R::c)) x = x * 10 + R::c - '0', R::c = getchar();\
	if (R::m) x = -x;\
} while(false)
namespace R { char c; bool m; }
using namespace std;

const int maxn = 40;
int n, m, l, r, tx, ty, a[maxn];
long long check[maxn], FULL_STEP;
bool G[maxn][maxn];

struct Queue {
	long long pin;
	short step;
} u, q[10000000];

int main() {
	
//	freopen("lights.out", "w", stdout);
	
	read(n);
	read(m);
	for (int i = 1; i <= n; i++)
		G[i][i] = 1;
	for (int i = 1; i <= m; i++) {
		read(tx);
		read(ty);
//		cout << tx << " " << ty << endl;
		G[tx][ty] = 1;
		G[ty][tx] = 1;
	}
	
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= n; j++)
//			cout << G[i][j];
//		puts("");
//	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = n; j > 0; j--)
			if (G[i][j]) a[i] = a[i] << 1 | 1;
			else a[i] = a[i] << 1;
	}
	FULL_STEP = check[1] = 1;
	for (int i = 2; i <= n; i++) {
		FULL_STEP = FULL_STEP << 1 | 1;
		check[i] = (check[i - 1] << 1);
	}
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= n; j++)
//			if (check[j] & a[i]) cout << 1;
//			else cout << 0;
//		cout << endl;
//	}
	
	l = r = 1, q[1] = {0, 0};
	while (l <= r) {
		u = q[l++];
//		cout << u.pin << " ";
//		for (int i = 1; i <= n; i++)
//			if (check[i] & u.pin) cout << 1;
//			else cout << 0;
//		cout << endl;
		for (int i = 1; i <= n; i++) {
			q[++r] = {u.pin ^ a[i], u.step + 1};
			if (q[r].pin == FULL_STEP) {
				printf("%d\n", q[r].step);
				return 0;
			}
		}
	} 
	
	return 0;
}