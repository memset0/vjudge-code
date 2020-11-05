#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e5 + 5, M = 6 * 1e5 + 5;
int n, ty[N], T, len, tr[M][26], cnt[N][2], ne[M], fail[M], last[N], vis[N]; //last保存上一次匹配的位置
char s[N], sp[N][10];
void add(int id) {
	int p = 0;
	for (int i = 0; sp[id][i]; i++) {
		int j = sp[id][i] - 'a';
		if (!tr[p][j]) tr[p][j] = ++len;
		p = tr[p][j];
	}
	if (!fail[p]) fail[p] = id;
	else {vis[id] = fail[p];} //代表重复的串 那么直接用前面的id就行了。 
} 
void build() {
	queue<int> q;
	for (int j = 0; j < 26; j++) {
		if (tr[0][j]) q.push(tr[0][j]);  
	}
	while (!q.empty()) {
		int p = q.front(); q.pop();
		for (int j = 0; j < 26; j++) {
			int c = tr[p][j];
			if (!c) tr[p][j] = tr[ne[p]][j];
			else {
				ne[c] = tr[ne[p]][j];
				q.push(c);
			}
		}
	}
	 
}
int main() {
	while (~scanf("%s%d", s, &n)) {
		memset(tr, 0, sizeof(tr));
		memset(ne, 0, sizeof(ne));
		memset(vis, 0, sizeof(vis));
		memset(fail, 0, sizeof(fail));
		memset(last, -1, sizeof(last)); len = 0;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++) {
			scanf("%d%s", &ty[i], sp[i]); add(i);
		} 
		build();
		for (int i = 0, j = 0; s[i]; i++) {
			int k = s[i] - 'a';
			j = tr[j][k];
			int t = j;
			while (t) {
				if (fail[t]) {
					cnt[fail[t]][0]++;
                	int cha = i - last[fail[t]] - strlen(sp[fail[t]]);
					if (cha >= 0) cnt[fail[t]][1]++, last[fail[t]] = i;;
				}	
				t = ne[t];
			}
		}
		printf("Case %d\n", ++T);
		for (int i = 1; i <= n; i++) {
			if (!vis[i])printf("%d\n", cnt[i][ty[i]]);
			else printf("%d\n", cnt[vis[i]][ty[i]]);
		}
		printf("\n");
	} 
	return 0;
} 