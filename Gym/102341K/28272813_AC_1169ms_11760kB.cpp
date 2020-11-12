#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 3e5 + 5;

int n, m, ans, a[N], nxt[N], str[N];

struct Node {
	int f, s[2], siz, xsiz;
	bool tag;
};
struct LinkCutTree {
    int vs, stc[N];
	Node V[N];
	inline bool isRight(int u) {
		return V[V[u].f].s[1] == u;
	}
	inline bool isRoot(int u) {
		return V[V[u].f].s[0] != u && V[V[u].f].s[1] != u;
	}
	inline void pushUp(int u) {
		V[u].siz = V[V[u].s[0]].siz + V[V[u].s[1]].siz + V[u].xsiz + 1;
	}
	inline void pushDown(int u) {
		if (V[u].tag) {
			V[u].tag = false;
			V[V[u].s[0]].tag ^= 1;
			V[V[u].s[1]].tag ^= 1;
			std::swap(V[u].s[0], V[u].s[1]);
		}
	}
	inline void connect(int u, int f, int dir) {
		V[u].f = f;
		V[f].s[dir] = u;
	}
	inline void rotate(int u) {
		int f = V[u].f, g = V[f].f, dir = isRight(u), fdir = isRight(f), s = V[u].s[dir ^ 1];
		V[u].f = g;
		if (!isRoot(f)) {
			V[g].s[fdir] = u;
		}
		connect(s, f, dir);
		connect(f, u, dir ^ 1);
		pushUp(f);
		pushUp(u);
	}
	void splay(int u) {
		int f = u;
		stc[vs = 1] = f;
		while (!isRoot(f)) {
			f = V[f].f;
			stc[++vs] = f;	
		}
		for (int i = vs; i >= 1; i--) {
			pushDown(stc[i]);
		}
		for (f = V[u].f; !isRoot(u); rotate(u), f = V[u].f) {
			if (!isRoot(f)) {
				rotate(isRight(u) == isRight(f) ? f : u);
			}
		}
	}
	void access(int u) {
		for (int s = 0; u > 0; s = u, u = V[u].f) {
			splay(u);
			V[u].xsiz += V[V[u].s[1]].siz - V[s].siz;
			V[u].s[1] = s;
			pushUp(u);
		}
	}
	void setRoot(int u) {
		access(u);
		splay(u);
		V[u].tag ^= 1;
	}
	void split(int u, int v) {
		setRoot(u);
		access(v);
		splay(v);
	}
	void link(int u, int v) {
		split(u, v);
		V[u].f = v;
		V[v].xsiz += V[u].siz;
		pushUp(v);
	}
    void cut(int u, int v) {
        split(u, v);
        V[v].s[0] = V[u].f = 0;
        pushUp(v);
    }
};

LinkCutTree lct;

void insert(int i, int c) {
    lct.V[i + 1].siz = 1; str[i] = c;
	if (i == 1) { lct.link(i + 1, nxt[i] + 1); return; }
	str[i] = c; nxt[i] = nxt[i - 1];
	while (nxt[i] > 0 && str[nxt[i] + 1] != str[i]) { nxt[i] = nxt[nxt[i]]; }
	if (str[nxt[i] + 1] == str[i]) { nxt[i]++; }
    lct.link(i + 1, nxt[i] + 1);
}

int main() {
    m = read();
	for (int i = 1, k; i <= m; i++) {
		char opt, c;
        std::cin >> opt;
		if (opt == 'g') {
			k = read();
			k = (k - 1 + ans) % n + 1;
            lct.cut(k + 1, nxt[k] + 1);
            lct.setRoot(k + 1); ans = lct.V[k + 1].siz;
            lct.link(k + 1, nxt[k] + 1);
			printf("%d\n", ans);
		} else {
			std::cin >> c; std::cin >> c; std::cin >> c;
			insert(++n, (((int) c - 'a') + ans) % 26 + 1);
		}
	}
}