// luogu-judger-enable-o2
// =================================
//   author: memset0
//   date: 2018.12.03 22:51:47
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
namespace ringo {
typedef long long ll;

template < class T >
inline void read(T &x) {
    x = 0; register char c = getchar(); register bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
}

template < class T >
inline void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) print(x / 10);
    putchar('0' + x % 10);
}

template < class T >
inline void print(T x, char c) {
    print(x), putchar(c);
}

const int N = 5e4 + 10, M = N * 22, mod = 1e9 + 7;
int n, m, l, r, x, y, z, ans, cnt, top;
int key[N], val[N], stk[M];

inline void sumd(int &a, int b) { a += b; if (a >= mod) a -= mod; }
inline void decd(int &a, int b) { a -= b; if (a < 0) a += mod; }
inline void muld(int &a, int b) { a = (ll)a * b % mod; }

struct treap_node {
    int key, val, sum, rnd, siz, ch[2];
} e[M];

struct segment_node {
    int l, r, mid, rt, sum;
} p[N << 2];

inline int new_node() { return top ? stk[top--] : ++cnt; }
inline int new_node(int key, int val) {
    int u;
    if (top) u = stk[top--], e[u].ch[0] = e[u].ch[1] = 0;
    else u = ++cnt, e[u].rnd = rand();
    e[u].key = key, e[u].val = e[u].sum = val;
    e[u].siz = 1;
    return u;
}

inline void update(int u) {
    e[u].siz = e[e[u].ch[0]].siz + e[e[u].ch[1]].siz + 1;
    e[u].sum = e[u].val;
	sumd(e[u].sum, e[e[u].ch[0]].sum);
	sumd(e[u].sum, e[e[u].ch[1]].sum);
}

int merge(int x, int y) {
    if (!x || !y) return x | y;
    if (e[x].rnd < e[y].rnd) {
        e[x].ch[1] = merge(e[x].ch[1], y);
        return update(x), x;
    } else {
        e[y].ch[0] = merge(x, e[y].ch[0]);
        return update(y), y;
    }
}

void split(int u, int k, int &x, int &y) {
    if (!u) { x = y = 0; return; }
    if (k < e[u].key) {
        y = u;
        split(e[y].ch[0], k, x, e[y].ch[0]);
    } else {
        x = u;
        split(e[x].ch[1], k, e[x].ch[1], y);
    }
    update(u);
}

void dfs(int u) {
    if (e[u].ch[0]) dfs(e[u].ch[0]);
    printf("%d ", e[u].key);
    if (e[u].ch[1]) dfs(e[u].ch[1]);
}

inline void erase(int &rt, int key) {
    split(rt, key - 1, x, y), split(y, key, y, z);
    stk[++top] = y;
    rt = merge(x, merge(merge(e[y].ch[0], e[y].ch[1]), z));
}

inline void insert(int &rt, int key, int val) {
    split(rt, key, x, y);
    rt = merge(x, merge(new_node(key, val), y));
}

void build(int u, int l, int r) {
    p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
	for (int i = l; i <= r; i++) {
        sumd(p[u].sum, val[i]);
		int u = ++cnt;
		e[u].val = e[u].sum = val[i];
		e[u].key = key[i];
		e[u].rnd = rand();
		e[u].siz = 1;
		while (top && e[u].rnd < e[stk[top]].rnd)
			e[u].ch[0] = stk[top], update(stk[top--]);
		update(u);
		if (top) e[stk[top]].ch[1] = u, update(stk[top]);
		stk[++top] = u;
	}
	while (top) update(stk[top--]);
	p[u].rt = stk[1];
	top = 0;
    if (l == r) return;
    build(u << 1, l, p[u].mid);
    build(u << 1 | 1, p[u].mid + 1, r);
}

void modify(int u, int k, int key, int val, int oldkey, int oldval) {
    erase(p[u].rt, oldkey), insert(p[u].rt, key, val);
    sumd(p[u].sum, val), decd(p[u].sum, oldval);
    if (p[u].l == p[u].r) return;
    if (k <= p[u].mid) modify(u << 1, k, key, val, oldkey, oldval);
    else modify(u << 1 | 1, k, key, val, oldkey, oldval);
}

int query(int u, int l, int r, int key, int val, bool flag) {
    // if (l > r) return 0;
    if (p[u].l == l && p[u].r == r) {
        int &rt = p[u].rt, ret;
        split(rt, key, x, y);
        if (flag) {
            ret = p[u].sum, decd(ret, e[x].sum);
            ret = (ret + (ll)val * e[y].siz) % mod;
        } else {
            ret = e[x].sum;
            ret = (ret + (ll)val * e[x].siz) % mod;
        }
        rt = merge(x, y);
        return ret;
    }
    if (r <= p[u].mid) return query(u << 1, l, r, key, val, flag);
    else if (l > p[u].mid) return query(u << 1 | 1, l, r, key, val, flag);
    else return (query(u << 1, l, p[u].mid, key, val, flag) +
        query(u << 1 | 1, p[u].mid + 1, r, key, val, flag)) % mod;
}

void output(int u) {
    printf("%d[%d %d] ", u, p[u].l, p[u].r);
    dfs(p[u].rt), putchar('\n');
    if (p[u].l == p[u].r) return;
    output(u << 1), output(u << 1 | 1);
}

inline int query(int k, int val) {
    int ret = 0;
    if (1 <= k - 1) sumd(ret, query(1, 1, k - 1, key[k], val, true)); // 大于
    if (k + 1 <= n) sumd(ret, query(1, k + 1, n, key[k] - 1, val, false)); // 小于
    return ret;
}

void main() {
    srand(20040725);
    read(n), read(m);;
    for (int i = 1; i <= n; i++)
        read(key[i]), read(val[i]);
    build(1, 1, n);
    // std::cerr << clock() / (double)CLOCKS_PER_SEC << std::endl;
    for (int i = 1; i < n; i++)
        sumd(ans, query(1, i + 1, n, key[i] - 1, val[i], false));
    // std::cerr << clock() / (double)CLOCKS_PER_SEC << std::endl;
    for (int i = 1; i <= m; i++) {
        read(l), read(r); if (l > r) std::swap(l, r);
		if (l != r) {
			decd(ans, query(l, val[l])); decd(ans, query(r, val[r]));
			std::swap(key[l], key[r]), std::swap(val[l], val[r]);
			modify(1, l, key[l], val[l], key[r], val[r]);
			modify(1, r, key[r], val[r], key[l], val[l]);
			sumd(ans, query(l, val[l])); sumd(ans, query(r, val[r]));
			if (key[l] > key[r]) decd(ans, val[l] + val[r]);
			else sumd(ans, (val[l] + val[r]) % mod);
		}
        print(ans, '\n');
    }
    // std::cerr << clock() / (double)CLOCKS_PER_SEC << std::endl;
    // std::cerr << cnt << std::endl;
}

} signed main() { return ringo::main(), 0; }