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

int n, x, ans, t, p, tot;
char a[1000010];
struct node {
	int ch[26], fail, sum;
	bool used;
} e[5000010];
void insert(char *a) {
	int len = strlen(a);
	p = 0;
	for (int i = 0; i < len; i++) {
		x = a[i] - 'a';
		if (!e[p].ch[x]) e[p].ch[x] = ++tot;
		p = e[p].ch[x];
	}
	e[p].sum++;
}
void build_fail() {
	queue < int > q;
	q.push(0);
	while (q.size()) {
		p = q.front(), q.pop();
		for (int i = 0; i < 26; i++)
			if (e[p].ch[i]) {
				if (!p) e[e[p].ch[i]].fail = 0;
				else {
					t = e[p].fail;
					while (t) {
						if (e[t].ch[i]) {
							e[e[p].ch[i]].fail = e[t].ch[i];
							break;
						}
						t = e[t].fail;
					}
					if (!t) e[e[p].ch[i]].fail = 0;
				}
				q.push(e[p].ch[i]);
			}
	}
}
void find(char *a) {
	int len = strlen(a);
	p = 0;
	for (int i = 0; i < len; i++) {
		x = a[i] - 'a';
		while (!e[p].ch[x] && p) p = e[p].fail;
		p = e[p].ch[x];
		if (!p) continue;
		t = p;
		while (t) {
			if (e[t].used) break;
			ans += e[t].sum;
			e[t].used = 1;
			t = e[t].fail;
		}
	}
}

int main() {
	scanf("%d", &n);
	while (n--) scanf("%s", a), insert(a);
	build_fail();
	scanf("%s", a), find(a);
	printf("%d\n", ans);
	return 0;
}