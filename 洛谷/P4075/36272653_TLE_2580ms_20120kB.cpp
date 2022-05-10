#include <bits/stdc++.h>
namespace ringo {
typedef long long ll;

template <class T> inline void read(T &x) {
    x = 0; register char c = getchar(); register bool f = 0;
    while (!isdigit(c)) f ^= c == '-', c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    if (f) x = -x;
}

const int OUT_LEN = 1000000; char obuf[OUT_LEN], *ooh = obuf;
inline void print(char c) {
	if (ooh == obuf + OUT_LEN) fwrite(obuf, 1, OUT_LEN, stdout), ooh = obuf;
	*ooh++ = c;
}
template<class T> inline void print(T x) {
	static int buf[30], cnt;
	if (!x) { print('0'); return; }
	if (x < 0) print('-'), x = -x;
	for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + '0';
	while (cnt) print((char)buf[cnt--]);
}
inline void flush() { fwrite(obuf, 1, ooh - obuf, stdout); }
template <class T> inline void print(T x, char c) { print(x), print(c); }

const int N = 1e5 + 10, p1 = 998244353, p2 = 1e9 + 7;
int t, n, m, u, v, ans, root, full_size;
int siz[N], maxp[N], sbkt[N], ebkt[N];
bool vis[N];
char a[N], b[N];
std::vector <int> G[N];

inline int dec(int a, int b, int mod) { a -= b; return a < 0 ? a + mod : a; }
inline int sub(int a, int b, int mod) { a += b; return a >= mod ? a - mod : a; }
inline int mul(int a, int b, int mod) { return (ll)a * b - (ll)a * b / mod * mod; }

struct pair {
    int a, b;
    inline pair operator+(const pair &other) const {
        return (pair){ sub(a, other.a, p1), sub(b, other.b, p2) };
    }
    inline pair operator-(const pair &other) const {
        return (pair){ dec(a, other.a, p1), dec(b, other.b, p2) };
    }
    inline pair operator*(const pair &other) const {
        return (pair){ mul(a, other.a, p1), mul(b, other.b, p2) };
    }
    inline bool operator==(const pair &other) const { return a == other.a && b == other.b; }
} invb, base;
pair pow[N], shash[N], ehash[N];

struct list {
	int top;
	int arr[N];
	void clear() { top = 0; }
	void push_back(int x) { arr[++top] = x; }
} rub;

struct status {
    int u, l;
    pair s, e;
};
std::vector<status> vet;

inline int g(int x) { return (x % m + m) % m; }
inline pair p(int x) { return (pair){ x, x }; }
inline char get() {
    char c;
    while (c = getchar(), !isupper(c))
        ;
    return c;
}
inline int inv(int x, int p) { return x < 2 ? 1 : (ll)(p - p / x) * inv(p % x, p) % p; }

inline void init() {
    ans = 0, memset(vis, 0, sizeof(vis));
    // for (int i = 1; i <= n; i++) G[i].clear();
	memset(G, 0, sizeof(G));
}

void get_root(int u, int father) {
    siz[u] = 1, maxp[u] = 0;
    for (auto v : G[u])
        if (!vis[v] && v != father) {
            get_root(v, u);
            siz[u] += siz[v], maxp[u] = std::max(maxp[u], siz[v]);
        }
    maxp[u] = std::max(maxp[u], full_size - siz[u]);
    if (maxp[u] < maxp[root])
        root = u;
}

void update_size(int u, int father) {
    siz[u] = 1;
    for (auto v : G[u])
        if (!vis[v] && v != father)
            update_size(v, u), siz[u] += siz[v];
}

void get_dis(int u, int father, int l, pair s, pair e) {
    ++l, s = s + p(a[u]) * pow[l - 1], e = e * base + p(a[u]);
    vet.push_back((status){ u, l, s, e });
    for (auto v : G[u])
        if (!vis[v] && v != father)
            get_dis(v, u, l, s, e);
}

void solve(int u) {
    vis[u] = 1;
    sbkt[0] = ebkt[0] = 1, rub.push_back(0);
    if (m == 1 && a[u] == b[1]) ++ans;
    for (auto v : G[u])
        if (!vis[v]) {
            get_dis(v, u, 1, p(a[u]), p(a[u]));
            for (auto i : vet) {
                int now = 0;
                if (i.s == shash[i.l])
                    now += ebkt[g(-i.l)];
                if (i.e == ehash[i.l])
                    now += sbkt[g(-i.l)];
                ans += now;
            }
            for (auto i : vet) {
                --i.l;
				i.s = (i.s - p(a[u])) * invb;
				i.e = i.e - p(a[u]) * pow[i.l];
                if (i.s == shash[i.l])
                    ++sbkt[g(i.l)];
                if (i.e == ehash[i.l])
                    ++ebkt[g(i.l)];
                rub.push_back(g(i.l));
            }
            vet.clear();
        }
	for (int i = 1; i <= rub.top; i++) sbkt[rub.arr[i]] = ebkt[rub.arr[i]] = 0;
    rub.clear();
    for (auto v : G[u])
        if (!vis[v]) {
            root = 0, full_size = maxp[root] = siz[v];
            get_root(v, u), solve(root);
        }
}

void main() {
    base = p(131), invb = (pair){ inv(131, p1), inv(131, p2) };
    for (read(t); t--;) {
        read(n), read(m), init();
        scanf("%s", a + 1);
        for (int i = 1; i <= n; i++) a[i] -= 'A' - 1;
        for (int i = 1; i < n; i++) {
            read(u), read(v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        scanf("%s", b + 1);
        for (int i = 1; i <= n; i++) b[i] -= 'A' - 1;
        b[0] = b[m], pow[0] = p(1);
        for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * base;
        for (int i = 1; i <= n; i++) shash[i] = shash[i - 1] * base + p(b[g(i)]);
        for (int i = 1; i <= n; i++) ehash[i] = ehash[i - 1] + p(b[g(1 - i)]) * pow[i - 1];
        root = 0, full_size = maxp[0] = n;
        get_root(1, 0), solve(root);
        print(ans, '\n');
    }
}

} signed main() { return ringo::main(), ringo::flush(), 0; }