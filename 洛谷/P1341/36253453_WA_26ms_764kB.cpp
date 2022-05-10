// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
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

int n, m, s, cnt, G[60][60], ind[60];

char readc() {
	char c = getchar();
	while (!isupper(c) && !islower(c)) c = getchar();
	return c;
}

int convert(char c) {
	if (isupper(c)) return c - 'A' + 1;
	if (islower(c)) return c - 'a' + 27;
	return -1;
}

char convert(int x) {
	if (x < 27) return x - 1 + 'A';
	if (x > 26) return x - 27 + 'a';
	return -1;
}

void dfs(int u) { 
	putchar(convert(u));
	for (int i = 1; i <= n; i++)
		if (G[u][i]) {
			G[u][i] = G[i][u] = 0;
			dfs(i);
			break;
		}
}

int main() {
	
	n = 52, m = read();
	for (int i = 1; i <= m; i++) {
		int u = convert(readc()), v = convert(readc());
		G[u][v] = G[v][u] = 1;
		ind[u]++, ind[v]++;
	}
	
	for (int i = 1; i <= n; i++)
		if (ind[i] & 1) {
			if (!s) s = i;
			cnt++;
		}
	if (cnt && cnt ^ 2) {
		puts("No Solution");
		return 0;
	}
	for (int i = 1; i <= n; i++)
		if (ind[i]) {
			if (!s) s = i;
			break;
		}
	dfs(s);

	return 0;
}
