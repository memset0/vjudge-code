// =================================
//   author: memset0
//   date: 2018.12.26 15:53:02
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, l, r) for (register int i = l; i <= r; i++)

namespace ringo {
typedef long long ll;
typedef unsigned long long ull;
template <class T> inline void read(T &x) {
	x = 0; register char c = getchar(); register bool f = 0;
	while (!isdigit(c)) f ^= c == '-', c = getchar();
	while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
	if (f) x = -x;
}
template <class T> inline void print(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) print(x / 10);
	putchar('0' + x % 10);
}
template <class T> inline void maxd(T &a, T b) { if (b > a) a = b; }
template <class T> inline void mind(T &a, T b) { if (b < a) a = b; }
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
template <class T> inline T abs(const T &a) { if (a < 0) return -a; return a; }

const int N = 2e5 + 10, p = 998244353;
int n, m, tim, nod, top;
int a[N], dfn[N], low[N], stk[N], f[N][3], g[N][2];
typedef std::vector <int> vector;
vector t[N];

#define walk(i, u, v, G) for (int i = G.hed[u], v = G.to[i]; i; i = G.nxt[i], v = G.to[i])
struct graph {
	int tot, hed[N], nxt[N << 1], to[N << 1];
	graph () { tot = 2; }
	inline void add(int u, int v) { nxt[tot] = hed[u], to[tot] = v, hed[u] = tot++; }
} G, P;

int inv(int x) { return !x || x == 1 ? 1 : (ll)(p - p / x) * inv(p % x) % p; }

inline int add(int x, int y) {
    x += y;
    if(x >= p) x -= p;
    return x;
}

inline int sub(int x, int y) {
    x -= y;
    if(x < 0) x += p;
    return x;
}

inline int mul(int x, int y) {
    return (ll)x * y % p;
}

inline int fpow(int x, int y) {
    int ans = 1;
    while(y) {
        if(y & 1) ans = mul(ans, x);
        y >>= 1; x = mul(x, x);
    }
    return ans;
}

namespace ntt {
    int base = 1, root = -1, maxbase = -1;
    std::vector <int> roots = {0, 1}, rev = {0, 1};
    
    void init() {
        int tmp = p - 1; maxbase = 0;
        while(!(tmp & 1)) {
            tmp >>= 1;
            maxbase++;
        }
        root = 2;
        while(1) {
            if(fpow(root, 1 << maxbase) == 1 && fpow(root, 1 << (maxbase - 1)) != 1) break;
            root++;
        }
    }
    
    void ensure_base(int nbase) {
        if(maxbase == -1) init();
        if(nbase <= base) return;
        assert(nbase <= maxbase);
        rev.resize(1 << nbase);
        for(register int i = 1; i < (1 << nbase); i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (nbase - 1));
        roots.resize(1 << nbase);
        while(base < nbase) {
            int z = fpow(root, 1 << (maxbase - base - 1));
            for(register int i = (1 << (base - 1)); i < (1 << base); i++) {
                roots[i << 1] = roots[i];
                roots[i << 1 | 1] = mul(roots[i], z);
            }
            base++;
        } 
    }
    
    void dft(std::vector <int> &a) {
        int n = a.size(), zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for(register int i = 0; i < n; i++) if(i < (rev[i] >> shift)) std::swap(a[i], a[rev[i] >> shift]);
        for(register int mid = 1; mid < n; mid <<= 1) {
            for(register int i = 0; i < n; i += (mid << 1)) {
                for(register int j = 0; j < mid; j++) {
                    int x = a[i + j], y = mul(a[i + j + mid], roots[mid + j]);
                    a[i + j] = add(x, y); a[i + j + mid] = sub(x, y);
                }
            }
        }
    }
    
    std::vector <int> pmul(std::vector <int> a, std::vector <int> b) {
        int need = a.size() + b.size() - 1, nbase = 0;
        while((1 << nbase) < need) nbase++;
        ensure_base(nbase); int size = 1 << nbase;
        a.resize(size); b.resize(size); dft(a); dft(b);
        int inv = fpow(size, p - 2);
        for(register int i = 0; i < size; i++) a[i] = mul(a[i], mul(b[i], inv));
        reverse(a.begin() + 1, a.end()); dft(a); a.resize(need); return a;
    }
}

using ntt::pmul;

void tarjan(int u, int from) {
	dfn[u] = low[u] = ++tim, stk[++top] = u;
	walk(i, u, v, P)
		if (!dfn[v]) {
			tarjan(v, i), mind(low[u], low[v]);
			if (low[v] == dfn[u]) {
				G.add(u, ++nod);
				do G.add(nod, stk[top]);
				while (stk[top--] != v);
			} else if (low[v] > dfn[u])
				G.add(u, v), top--;
		} else if ((i ^ 1) != from) mind(low[u], dfn[v]);
}

vector solve(int l, int r) {
	if (l == r) return t[l];
	int mid = (l + r) >> 1; vector _l = solve(l, mid), _r = solve(mid + 1, r);
	return pmul(_l, _r);
}

void dfs(int u) {
	walk(i, u, v, G) dfs(v);
	if (u <= n) {
		if (!G.hed[u]) { f[u][0] = a[u] >= 0, f[u][1] = a[u] >= 1, f[u][2] = a[u] >= 2; return; }
		int cnt = 0;
		walk(i, u, v, G) {
			t[++cnt].clear();
			if (v <= n) t[cnt].pb(f[v][1]), t[cnt].pb(f[v][0]);
			else t[cnt].pb(f[v][2]), t[cnt].pb(f[v][1]), t[cnt].pb(f[v][0]);
		}
		vector now = solve(1, cnt); now.resize(a[u] + 1);
		for (int i = 1; i < (int)now.size(); i++) now[i] = (now[i] + now[i - 1]) % p;
		if (a[u] >= 0) f[u][0] = now[a[u]];
		if (a[u] >= 1) f[u][1] = now[a[u] - 1];
		if (a[u] >= 2) f[u][2] = now[a[u] - 2];
	} else {
        std::vector <int> son;
        walk(i, u, v, G) son.pb(v);
        for (int pre = 0; pre < 2; pre++) {
            g[0][pre] = 1, g[0][pre ^ 1] = 0; 
            for (int i = 0, v; i < (int)son.size(); i++) {
                v = son[i];
                g[i + 1][0] = ((ll)g[i][0] * f[v][1] + (ll)g[i][1] * f[v][2]) % p;
                g[i + 1][1] = ((ll)g[i][0] * f[v][0] + (ll)g[i][1] * f[v][1]) % p;
            }
            if (pre) (f[u][2] += g[son.size()][0]) %= p, (f[u][1] += g[son.size()][1]) %= p;
            else (f[u][1] += g[son.size()][0]) %= p, (f[u][0] += g[son.size()][1]) %= p;
        }
    }
}

void main() {
	read(n), read(m);
	for (int i = 1, u, v; i <= m; i++) read(u), read(v), P.add(u, v), P.add(v, u);
	for (int i = 1; i <= n; i++) read(a[i]);
	nod = n, tarjan(1, 0), dfs(1);
	print(f[1][0], '\n');
}

} signed main() { return ringo::main(), 0; }
