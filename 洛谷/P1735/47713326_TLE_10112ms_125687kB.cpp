#include <bits/stdc++.h>
using namespace std;
const int maxn = 1410;
const int Amov[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int Bmov[4][2] = {{2, 0}, {0, 2}, {-2, 0}, {0, -2}};
const int Cmov[4][2] = {{1, 1}, {-1, -1}, {-1, 1}, {1, -1}};
int n, dis[maxn * maxn];
short int a[maxn][maxn], cge[256];
bool in_q[maxn * maxn];
struct G_link {
	int nxt, v;
} v;
vector < G_link > G[maxn * maxn];
queue < int > q;
int read() {
	char c = getchar();
	while (!(c == '*' || c == 'A' || c == 'B' || c == 'C')) c = getchar();
	return cge[c];
}
void link(int x, int y, int xx, int yy, int v) {
	int l = n * (x - 1) + y, r = n * (xx - 1) + yy;
//	cout << l << " "  << r << endl;
	G[l].push_back({r, v});
}
int main() {
	int vx, vy, u;
	memset(dis, 63, sizeof(dis));
	cge['*'] = 0; cge['A'] = 1; cge['B'] = 2; cge['C'] = 3;
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] = read();
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (a[i][j]) {
				if (a[i][j] == 1) {
					for (int v = 0; v < 4; v++) {
						vx = i + Amov[v][0];
						vy = j + Amov[v][1];
						if (a[vx][vy] && vx > 0 && vy > 0 && vx <= n && vy <= n) {
							link(i, j, vx, vy, 1);
						}
					}
				} else if (a[i][j] == 2) {
					for (int v = 0; v < 4; v++) {
						vx = i + Bmov[v][0];
						vy = j + Bmov[v][1];
						if (a[vx][vy] && vx > 0 && vy > 0 && vx <= n && vy <= n) {
							link(i, j, vx, vy, 1);
						}
					}
				} else if (a[i][j] == 3) {
					for (int v = 0; v < 4; v++) {
						vx = i + Cmov[v][0];
						vy = j + Cmov[v][1];
						if (a[vx][vy] && vx > 0 && vy > 0 && vx <= n && vy <= n) {
							link(i, j, vx, vy, 2);
						}
					}
				}
			}
		}
	
	q.push(1); q.push(n); q.push(n * n - n + 1);
	in_q[1] = in_q[n] = in_q[n * n - n + 1] = 1;
	dis[1] = dis[n] = dis[n * n - n + 1] = 1;
	while (q.size()) {
		u = q.front(); q.pop();
		in_q[u] = 0;
		for (int k = 0; k < G[u].size(); k++) {
			v = G[u][k];
			if (dis[v.nxt] > dis[u] + v.v) {
				dis[v.nxt] = dis[u] + v.v;
				if(!in_q[v.nxt])
				{
					in_q[v.nxt] = 1;
					q.push(v.nxt);
				}
			}
		}
	}
	if (dis[n * n] != 1061109567) cout << dis[n * n] << endl;
	else cout << "No answer" << endl;
//	for (int i = 1; i <= n; i++) {
//		for (int j = 1; j <= n; j++)
//			printf("%d ", dis[(i - 1) * n + j]);
//		puts("");
//	}
}
