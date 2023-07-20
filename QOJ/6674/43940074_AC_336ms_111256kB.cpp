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

const int N = 3e5 + 5;

struct SegmentTree {
    int f[N * 4];

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
    void modify(int u, int l, int r, int p, int x) {
        if (l + 1 >= r) { f[u] += x; return; }
        int mid = l + r >> 1;
        if (p < mid) {
            modify(u << 1, l, mid, p, x);
        } else {
            modify(u << 1 | 1, mid, r, p, x);
        }
        pushUp(u);
    }
    void query(int u, int l, int r, int pl, int pr, ll& res) {
        if (pl >= pr) { return; }
        if (l == pl && r == pr) { res += f[u]; return; }
        int mid = l + r >> 1;
        if (pr <= mid) {
            query(u << 1, l, mid, pl, pr, res);
        } else if (pl >= mid) {
            query(u << 1 | 1, mid, r, pl, pr, res);
        } else {
            query(u << 1, l, mid, pl, mid, res);
            query(u << 1 | 1, mid, r, mid, pr, res);
        }
        pushUp(u);
    }
} smt;

const int L = 20;

int n, dep[N], ft[L][N], max[L][N], min[L][N], a[N], b[N];
std::vector<int> e[N];

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    ft[0][u] = fa; max[0][u] = min[0][u] = u;
    for (int i = 1; i < L; i++) {
        ft[i][u] = ft[i - 1][ft[i - 1][u]];
        max[i][u] = std::max(max[i - 1][u], max[i - 1][ft[i - 1][u]]);
        min[i][u] = std::min(min[i - 1][u], min[i - 1][ft[i - 1][u]]);
    }
    for (auto v : e[u]) {
        if (v == fa) { continue; }
        dfs(v, u);
    }
}

std::pair<int, int> get(int u, int v) {
    if (dep[u] < dep[v]) { std::swap(u, v); }
    int delt = dep[u] - dep[v], _min_ = std::min(u, v), _max_ = std::max(u, v);
    for (int i = L - 1; i >= 0; i--) {
        if (delt >> i & 1) {
            _max_ = std::max(_max_, max[i][u]);
            _min_ = std::min(_min_, min[i][u]);
            u = ft[i][u];
        }
    }
    if (u != v) {
        for (int i = L - 1; i >= 0; i--) {
            if (ft[i][u] != ft[i][v]) {
                _max_ = std::max({_max_, max[i][u], max[i][v]});
                _min_ = std::min({_min_, min[i][u], min[i][v]});
                u = ft[i][u]; v = ft[i][v];
            }
        }
        _max_ = std::max({_max_, ft[0][u], u, v});
        _min_ = std::min({_min_, ft[0][u], u, v});
    }
    return {_max_, _min_};
}

void run() {
    in >> n;
    for (int u = 1; u <= n; u++) { e[u].clear(); }
    for (int i = 1; i < n; i++) {
        int u, v;
        in >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs(1, 0);
    smt.build(1, 0, n + 2);
    ll ans = n;
    a[0] = n + 1;
    std::stack<int> stc; stc.push(0);
    std::stack<int> stack;
    for (int u = 2; u <= n; u++) {
        int v = u - 1;
        auto [_max_, _min_] = get(u, v);
        a[v] = _max_; b[v] = _min_; 
        while (a[stc.top()] <= a[v]) { stc.pop(); }
        if (b[v] == v) {
            stack.push(v);
            smt.modify(1, 0, n + 2, v, 1);
        } else {
            while (!stack.empty() && b[stack.top()] > b[v]) {
                smt.modify(1, 0, n + 2, stack.top(), -1);
                stack.pop();
            }
        }
        if (a[v] <= u) {
            int low = stc.top() + 1;
            smt.query(1, 0, n + 2, low, n + 2, ans);
        }
        stc.push(v);
    }
    out << ans << "\n";
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