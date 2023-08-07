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

constexpr int mod = 998244353;
using Z = ModInt<mod>;

const int N = 2e5 + 5;

struct SegmentTree {
    Z f[N * 4], tag[N * 4];

    void pushUp(int u) {
        f[u] = f[u << 1] + f[u << 1 | 1];
    }
    void pushTag(int u, Z x) {
        f[u] *= x; tag[u] *= x;
    }
    void pushDown(int u) {
        if (tag[u].x != 1) {
            pushTag(u << 1, tag[u]);
            pushTag(u << 1 | 1, tag[u]);
            tag[u] = 1;
        }
    }

    void build(int u, int l, int r) {
        f[u] = 0; tag[u] = 1;
        if (l + 1 >= r) { return; }
        int mid = l + r >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid, r);
    }
    void modify(int u, int l, int r, int p, Z x) {
        if (l + 1 >= r) { f[u] += x; return; }
        int mid = l + r >> 1;
        pushDown(u);
        if (p < mid) {
            modify(u << 1, l, mid, p, x);
        } else {
            modify(u << 1 | 1, mid, r, p, x);
        }
        pushUp(u);
    }
    void modify(int u, int l, int r, int pl, int pr, Z x) {
        if (pl >= pr) { return; }
        if (l == pl && r == pr) { pushTag(u, x); return; }
        int mid = l + r >> 1;
        pushDown(u);
        if (pr <= mid) {
            modify(u << 1, l, mid, pl, pr, x);
        } else if (pl >= mid) {
            modify(u << 1 | 1, mid, r, pl, pr, x);
        } else {
            modify(u << 1, l, mid, pl, mid, x);
            modify(u << 1 | 1, mid, r, mid, pr, x);
        }
        pushUp(u);
    }
    void query(int u, int l, int r, int pl, int pr, Z& res) {
        if (pl >= pr) { return; }
        if (l == pl && r == pr) { res += f[u]; return; }
        int mid = l + r >> 1;
        pushDown(u);
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
} smt[2];

struct Seg {
    int l, r, c;
} a[N];

int n, m;
std::vector<int> tb;

void run() {
    in >> n;
    tb.clear();
    tb.push_back(0);
    for (int i = 0; i < n; i++) {
        int l, r, c;
        in >> l >> r >> c;
        a[i] = {l, r, c};
        tb.push_back(l);
        tb.push_back(r);
    }
    std::sort(tb.begin(), tb.end());
    m = std::unique(tb.begin(), tb.end()) - tb.begin();
    tb.resize(m);
    for (int i = 0; i < n; i++) {
        a[i].l = std::lower_bound(tb.begin(), tb.end(), a[i].l) - tb.begin();
        a[i].r = std::lower_bound(tb.begin(), tb.end(), a[i].r) - tb.begin();
    }
    std::sort(a, a + n, [&](Seg x, Seg y) { return x.r < y.r || (x.r == y.r && x.l < y.l); });
    smt[0].build(1, 0, m); smt[0].modify(1, 0, m, 0, 1);
    smt[1].build(1, 0, m); smt[1].modify(1, 0, m, 0, 1);
    Z ans = 1;
    for (int i = 0; i < n; i++) {
        auto [l, r, c] = a[i];
        Z res = 0;
        smt[c ^ 1].query(1, 0, m, 0, l, res);
        smt[c ^ 1].modify(1, 0, m, 0, l, 2);
        smt[c].modify(1, 0, m, r, res);
        ans += res;
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