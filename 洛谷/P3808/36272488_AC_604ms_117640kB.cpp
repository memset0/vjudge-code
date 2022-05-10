#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 1000010;
int n, x, ans;
char a[maxn], s[maxn];
struct node {
	node *next[26];
	node *fail;
	int sum;
	bool got;
};
node *root;
node *newd;
node *newnode() {
	newd = (struct node*)malloc(sizeof(struct node));
    for (int j = 0; j < 26; j++)
		newd->next[j] = 0;
    newd->sum = newd->got = 0;
	newd->fail = 0;
	return newd;
}
void insert(char *a) {
	node *p = root;
	int len = strlen(a);
	for (int i = 0; i < len; i++) {
		x = a[i] - 'a';
		if (p->next[x] == NULL) {
            p->next[x] = newnode();
		}
		p = p->next[x];
	}
	p->sum++;
}
void build_fail(void)  {
	queue < node* > q;
	q.push(root);
	node *p;
	node *u;
	while (q.size()) {
		u = q.front(), q.pop();
		for (int i = 0; i < 26; i++)
			if (u->next[i] != NULL) {
				if (u == root)
					u->next[i]->fail = root;
				else {
					p = u->fail;
					while (p) {
						if (p -> next[i]) {
							u->next[i]->fail = p->next[i];
							break;
						}
						p = p->fail;
					}
					if (p == NULL) u->next[i]->fail = root;
				}
				q.push(u->next[i]);
			}
	}
}
void find(char *a) {
	node *u = root;
	node *p;
	int len = strlen(a);
	for (int i = 0; i < len; i++) {
		x = a[i] - 'a';
		while (u->next[x] == NULL && u != root) u = u->fail;
		u = u->next[x];
		if (!p) p = root;
		p = u;
		while (p != root) {
			if (p->got) break;
			ans += p->sum;
			p->sum = 0;
			p->got = 1;
			p = p->fail;
		}
	}
}
int main() {
	root = newnode();
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", a);
		insert(a);
	}
	build_fail();
	scanf("%s", a);
	find(a);
	printf("%d\n", ans);
	return 0;
}
