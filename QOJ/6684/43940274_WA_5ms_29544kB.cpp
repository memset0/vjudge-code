#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;

namespace fox {
template <class T>
constexpr T pow(T x, ll y) {
    T r = 1;
    for (; y > 0; y /= 2, x = x * x)
        if (y % 2 == 1) r = x * r;
    return r;
}
} // namespace fox

struct Scanner {
    FILE* stream;
    Scanner(FILE* s) : stream(s) {}
    char buf[1 << 20], *l = buf, *r = buf;
    bool flush() { l = buf; r = l + fread(buf, 1, 1 << 20, stream); return l == r; }
    void get(char& c) { c = l == r && flush() ? ' ' : *l++; }
    friend Scanner& operator >>(Scanner& in, char& c) { return in.get(c), in; }
    friend Scanner& operator >>(Scanner& in, char* s) {
        for (in.get(s[0]); isspace(s[0]); in.get(s[0]));
        for (int i = 0; !isspace(s[i]) || (s[i] = '\0'); i++) in.get(s[i + 1]);
        return in;
    }
    friend Scanner& operator >>(Scanner& in, std::string& s) {
        char c;
        for (in.get(c); isspace(c); in.get(c));
        for (s = ""; !isspace(c); in.get(c)) s += c;
        return in;
    }
    template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
    friend Scanner& operator >>(Scanner& in, T& x) {
        char c, f = '+';
        for (in.get(c); !isdigit(c); in.get(c))
            if constexpr (std::is_signed_v<T>) f = c;
        for (x = 0; isdigit(c); in.get(c)) x = x * 10 + c - '0';
        if constexpr (std::is_signed_v<T>) x = f == '-' ? -x : x;
        return in;
    }
    template <class T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
    friend Scanner& operator >>(Scanner& in, T& x) {
        std::string s; in >> s; x = std::stod(s);
        return in;
    }
    template <class T, class U>
    friend Scanner& operator >>(Scanner& in, std::pair<T, U>& a) {
        return in >> a.first >> a.second;
    }
    template <class T, size_t S>
    friend Scanner& operator >>(Scanner& in, std::array<T, S>& a) {
        for (int i = 0, n = S; i < n; i++) in >> a[i];
        return in;
    }
    template <class T>
    friend Scanner& operator >>(Scanner& in, std::vector<T>& a) {
        for (int i = 0, n = a.size(); i < n; i++) in >> a[i];
        return in;
    }
};

struct Printer {
    FILE* stream;
    Printer(FILE* s) : stream(s) {}
    char buf[1 << 20], *l = buf, *r = buf + (1 << 20) - 1;
    int format = 0, precision = 15;
    ~Printer() { flush(); }
    void flush() { fwrite(buf, 1, l - buf, stream); l = buf; }
    void put(const char& c) { *l++ = c; if (l == r) flush(); }
    friend Printer& operator <<(Printer& out, const char& c) { return out.put(c), out; }
    friend Printer& operator <<(Printer& out, const char* s) {
        for (int i = 0; s[i] != '\0'; i++) out.put(s[i]);
        return out;
    }
    friend Printer& operator <<(Printer& out, const std::string& s) {
        for (int i = 0, n = s.size(); i < n; i++) out.put(s[i]);
        return out;
    }
    template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
    friend Printer& operator <<(Printer& out, T x) {
        static char s[40];
        static int i = 0;
        if (x == 0) { out.put('0'); return out; }
        if constexpr (std::is_signed_v<T>) x = x < 0 ? out.put('-'), -x : x;
        while (x > 0) s[++i] = x % 10 + '0', x /= 10;
        while (i > 0) out.put(s[i--]);
        return out;
    }
    template <class T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
    friend Printer& operator <<(Printer& out, T x) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(out.precision) << x;
        return out << oss.str();
    }
    template <class T, class U>
    friend Printer& operator <<(Printer& out, const std::pair<T, U>& a) {
        return out << a.first << " \n"[out.format > 1] << a.second;
    }
    template <class T, size_t S>
    friend Printer& operator <<(Printer& out, const std::array<T, S>& a) {
        out << a[0];
        for (int i = 1, n = S; i < n; i++) out << " \n"[out.format > 1] << a[i];
        return out;
    }
    template <class T>
    friend Printer& operator <<(Printer& out, const std::vector<T>& a) {
        if (!a.empty()) out << a[0];
        for (int i = 1, n = a.size(); i < n; i++) out << " \n"[out.format > 0] << a[i];
        return out;
    }
};

Scanner in(stdin);
Printer out(stdout), err(stderr);

template <int mod>
struct ModInt {
    int x;
    constexpr ModInt() : x(0) {}
    template <class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
    constexpr ModInt(T x) : x((x % mod + mod) % mod) {}
    constexpr ModInt inv() const { assert(x > 0); return fox::pow(*this, mod - 2); }
    constexpr ModInt operator -() const { if (x == 0) return 0; return mod - x; }
    constexpr ModInt& operator ++() { if ((++x) == mod) x = 0; return *this; }
    constexpr ModInt& operator --() { if ((--x) == -1) x = mod - 1; return *this; }
    constexpr ModInt operator ++(int) { ModInt n(*this); ++*this; return n; }
    constexpr ModInt operator --(int) { ModInt n(*this); --*this; return n; }
    constexpr ModInt& operator +=(const ModInt& rhs) { if ((x += rhs.x) >= mod) x -= mod; return *this; }
    constexpr ModInt& operator -=(const ModInt& rhs) { if ((x -= rhs.x) < 0) x += mod; return *this; }
    constexpr ModInt& operator *=(const ModInt& rhs) { x = (ll) x * rhs.x % mod; return *this; }
    constexpr ModInt& operator /=(const ModInt& rhs) { x = (ll) x * rhs.inv().x % mod; return *this; }
    constexpr friend bool operator <(const ModInt& lhs, const ModInt& rhs) { return lhs.x < rhs.x; }
    constexpr friend bool operator ==(const ModInt& lhs, const ModInt& rhs) { return lhs.x == rhs.x; }
    constexpr friend bool operator !=(const ModInt& lhs, const ModInt& rhs) { return lhs.x != rhs.x; }
    constexpr friend ModInt operator +(const ModInt& lhs, const ModInt& rhs) { return ModInt(lhs) += rhs; }
    constexpr friend ModInt operator -(const ModInt& lhs, const ModInt& rhs) { return ModInt(lhs) -= rhs; }
    constexpr friend ModInt operator *(const ModInt& lhs, const ModInt& rhs) { return ModInt(lhs) *= rhs; }
    constexpr friend ModInt operator /(const ModInt& lhs, const ModInt& rhs) { return ModInt(lhs) /= rhs; }
    friend Scanner& operator >>(Scanner& in, ModInt& n) { ll x; in >> x; n = ModInt(x); return in; }
    friend Printer& operator <<(Printer& out, const ModInt& n) { return out << n.x; }
};

namespace fox::combinatorics {
template <int mod>
struct Factor {
    int len;
    std::vector<std::array<ModInt<mod>, 3>> f;
    Factor() : len(2), f{{0, 1, 1}, {1, 1, 1}} {}
    void build(int n) {
        if (n < len) return;
        len *= 2; f.resize(len);
        for (int i = len / 2; i < len; i++) {
            f[i][0] = f[mod % i][0] * (mod - mod / i);
            f[i][1] = f[i - 1][1] * i;
            f[i][2] = f[i - 1][2] * f[i][0];
        }
        build(n);
    }
    ModInt<mod> inv(int n) { build(n); return f[n][0]; }
    ModInt<mod> fac(int n) { build(n); return f[n][1]; }
    ModInt<mod> invfac(int n) { build(n); return f[n][2]; }
    ModInt<mod> binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
    ModInt<mod> catalan(int n, int m) /* OEIS A009766 */ {
        if (n < m || m < 0) return 0;
        return fac(n + m) * invfac(m) * invfac(n + 1) * (n + 1 - m);
    }
};

template <int mod>
struct Power {
    int len, base;
    std::vector<ModInt<mod>> f, g;
    Power(int b) : len(std::sqrt(mod) + 1), base(b), f{1}, g{1} {
        f.resize(len + 1); g.resize(len);
        for (int i = 1; i <= len; i++)
            f[i] = f[i - 1] * base;
        for (int i = 1; i < len; i++)
            g[i] = g[i - 1] * f[len];
    }
    ModInt<mod> get(ll n) {
        n = (n % (mod - 1) + mod - 1) % (mod - 1);
        return f[n % len] * g[n / len];
    }
};
} // namespace fox::combinatorics

constexpr int mod = 1004535809, base = 6011;
using Z = ModInt<mod>;
fox::combinatorics::Factor<mod> comb;
fox::combinatorics::Power<mod> pwr(6011);

const int N = 2e5 + 5;

int dep[N], shift, ord[N];

struct SegmentTree {
    Z f[N * 4];

    void pushUp(int u) {
        f[u] = f[u << 1] + f[u << 1 | 1];
    }

    void build(int u, int l, int r) {
        f[u] = 0;
        if (l + 1 >= r) { return; }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid, r);
    }
    void modify(int u, int l, int r, int p, Z x) {
        if (l + 1 >= r) { f[u] = x; return; }
        int mid = l + r >> 1;
        if (p < mid) {
            modify(u << 1, l, mid, p, x);
        } else {
            modify(u << 1 | 1, mid, r, p, x);
        }
        pushUp(u);
    }
    void query(int u, int l, int r, int pl, int pr, Z& now, std::vector<Z>& sour, int& res) {
        if (pl >= pr) { return; }
        if (l == pl && r == pr) {
            if (now + f[u] == sour[dep[ord[r - 1]] - shift]) { now += f[u]; return; }
            if (l + 1 >= r) { res = ord[l]; return; }
            int mid = l + r >> 1;
            query(u << 1 | 1, mid, r, mid, pr, now, sour, res);
            if (res != -1) { return; }
            query(u << 1 | 1, mid, r, mid, pr, now, sour, res);
            return;
        }
        int mid = l + r >> 1;
        if (pr <= mid) {
            query(u << 1, l, mid, pl, pr, now, sour, res);
        } else if (pl >= mid) {
            query(u << 1 | 1, mid, r, pl, pr, now, sour, res);
        } else {
            query(u << 1, l, mid, pl, mid, now, sour, res);
            if (res != -1) { return; }
            query(u << 1 | 1, mid, r, mid, pr, now, sour, res);
        }
    }
} smt;

int n, par[N], ft[N], siz[N], hs[N], top[N];
int tms, dfn[N];
int m, key[N], keyid[N], ans[N];
std::vector<int> son[N], keys[N];
std::vector<Z> pre[N];

void dfs1(int u, int fa) {
    ft[u] = fa; dep[u] = dep[fa] + 1; siz[u] = 1; hs[u] = -1;
    for (auto v : son[u]) {
        dfs1(v, u);
        siz[u] += siz[v];
        if (hs[u] == -1 || siz[hs[u]] < siz[v]) { hs[u] = v; }
    }
}
void dfs2(int u, int tp) {
    top[u] = tp; dfn[u] = tms; ord[tms++] = u;
    if (hs[u] != -1) { dfs2(hs[u], tp); }
    for (auto v : son[u]) {
        if (v == hs[u]) { continue; }
        dfs2(v, v);
    }
}

void checkFinished(int u) {
    if (top[u] != u) { return; }
    Z now = 0;
    for (int v = u; v != -1; v = hs[v]) {
        now += ans[v] * pwr.get(dep[v]);
        pre[u].push_back(now);
    }
}

int check(int u, int rtu, int v, int rtv) {
    std::vector<std::array<int, 2>> datau, datav;
    int w = u;
    while (top[w] != top[rtu]) {
        datau.push_back({top[w], w});
        w = ft[top[w]];
    }
    datau.push_back({rtu, w});
    w = v;
    while (top[w] != top[rtv]) {
        datau.push_back({top[w], w});
        w = ft[top[w]];
    }
    datau.push_back({rtv, w});
    std::reverse(datau.begin(), datau.end());
    std::reverse(datav.begin(), datav.end());
    for (int i = 0, j = 0; i < datau.size() || j < datav.size(); ) {
        if (i == datau.size()) { return 1; }
        if (j == datav.size()) { return 0; }
        int nxt = std::min(dep[datau[i][1]], dep[datav[i][1]]);
        if (dep[datau[i][0]] <= dep[datav[i][0]]) {
            shift = dep[datav[i][0]];
            // smt.query(1, 0, tms, pre[v]);
        } else {
            
        }
        if (nxt == dep[datau[i][1]]) { i++; }
        if (nxt == dep[datav[i][1]]) { j++; }
    }
    return 2;
}

void dfs(int u) {
    std::vector<int> sons;
    for (auto v : son[u]) {
        dfs(v); sons.push_back(v);
    }
    std::sort(sons.begin(), sons.end(), [&] (int i, int j) {
        for (int ind = 0; ; ind++) {
            if (ind == keys[i].size()) { return true; }
            if (ind == keys[j].size()) { return false; }
            int res = check(keys[i][ind], i, keys[j][ind], j);
            if (res == 2) { continue; }
            return res == 1;
        }
        return false;
    });
    if (keyid[u]) { keys[u].push_back(u); }
    int mark = 0;
    for (auto v : sons) {
        ans[v] = mark++;
        smt.modify(1, 0, tms, dfn[v], ans[v] * pwr.get(dep[v]));
        if (keys[u].size() < keys[v].size()) {
            std::swap(keys[u], keys[v]);
        }
        for (auto w : keys[v]) { keys[u].push_back(w); }
        checkFinished(v);
    }
}

void run() {
    in >> n >> m;
    for (int u = 0; u <= n; u++) {
        son[u].clear();
        keys[u].clear(); keyid[u] = 0;
        pre[u].clear();
    }
    for (int u = 1; u <= n; u++) {
        in >> par[u];
        son[par[u]].push_back(u);
    }
    for (int i = 1; i <= m; i++) {
        in >> key[i];
        keyid[key[i]] = i;
    }
    tms = 0; dfs1(0, -1); dfs2(0, 0);
    smt.build(1, 0, tms);
    dfs(0);
    for (int u = 1; u <= n; u++) {
        out << (char) ('a' + ans[u]);
    }
    out << "\n";
}

int main() {
#ifdef SULFOX
    freopen("#.in", "r", stdin);
    freopen("#.out", "w", stdout);
#endif
    int t = 1;
    in >> t;
    for (int i = 0; i < t; i++) { run(); }
    return 0;
}