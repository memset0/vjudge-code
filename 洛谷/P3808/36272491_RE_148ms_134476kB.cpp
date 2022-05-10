#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n, x, ans;
char a[1000010];
struct node {
	node *next[26], *fail;
	int sum; bool got;
} *root, *newd, *p, *t;
node *newnode() {
	newd = (struct node*)malloc(sizeof(struct node));
	for (int i = 0; i < 26; i++)
		newd->next[i] = 0;
	newd->sum = newd->got = 0;
	newd->fail = 0;
	return newd;
}
void insert(char *a) {
	int len = strlen(a);
	p = root;
	for (int i = 0; i < len; i++) {
		x = a[i] - 'a';
		if (p->next[x] == NULL)
			p->next[x] = newnode();
		p = p->next[x];
	}
	p->sum++;
}
void build_fail() {
	queue < node* > q;
	q.push(root);
	while (q.size()) {
		p = q.front(), q.pop();
		for (int i = 0; i < 26; i++)
			if (p->next[i] != NULL) {
				if (p == root) p->next[i]->fail = root;
				else {
					t = p->fail;
					while (t) {
						if (t->next[i]) {
							p->next[i]->fail = t->next[i];
							break;
						}
						t = t->fail;
					}
					if (!p) p->next[i]->fail = root;
				}
			}
	}
}
void find(char *a) {
	int len = strlen(a);
	p = root;
	for (int i = 0; i < len; i++) {
		x = a[i] - 'a';
		while (!p->next[x] && p != root) p = p->fail;
		if (!p->next[x]) continue;
		p = p->next[x];
		t = p;
		while (t) {
			if (t->got) break;
			ans += t->sum;
			t->sum = 0;
			t->got = 1;
			t = t->fail;
		}
	} 
}

int main() {
	root = newnode();
	scanf("%d\n", &n);
	while (n--) gets(a), insert(a);
	build_fail();
	gets(a), find(a);
	printf("%d\n", ans);
	return 0;
}
