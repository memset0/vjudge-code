#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long;

template <class T> constexpr T inf = 1e100;
template <> constexpr int inf<int> = 1e9 + 7;
template <> constexpr ll inf<ll> = 4e18;

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

const int N = 1000005;

int m, qry[N];
std::vector<std::pair<int, int>> e[N];

void clear() {
    for (int i = 0; i < m; i++) {
        e[qry[i]].clear();
    }
}

void run() {
    in >> m;
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        int opt, k, x;
        in >> opt >> k >> x;
        qry[i] = k;
        if (k <= 1000000) {
            e[k].push_back({opt, x});
        } else if (opt == 1) {
            ans = -1;
        }
    }
    if (ans == -1) { out << "0\n"; clear(); return; }
    int sl = inf<int>, sr = 1;
    std::vector<std::pair<int, int>> a;
    for (int _k = 0; _k < m; _k++) {
        int k = qry[_k];
        if (e[k].empty()) { continue; }
        for (auto [opt, x] : e[k]) {
            int l = -1, r = -1;
            for (int low = 1, high = x, mid; low <= high; ) {
                mid = low + high >> 1;
                if (1ll * k * (0ll + mid + mid + k - 1) / 2 <= x) {
                    low = mid + 1; l = mid;
                } else {
                    high = mid - 1;
                }
            }
            for (int low = 1, high = x, mid; low <= high; ) {
                mid = low + high >> 1;
                if (1ll * k * (0ll + mid + mid - k + 1) / 2 >= x) {
                    high = mid - 1; r = mid;
                } else {
                    low = mid + 1;
                }
            }
            if (opt == 1) {
                if (l == -1) { out << "0\n"; clear(); return; }
                sl = std::min(sl, l); sr = std::max(sr, r);
            } else {
                if (l == -1) { continue; }
                a.push_back({l, r});
            }
        }
        e[k].clear();
    }
    for (auto& p : a) {
        p.first = std::min(p.first, sl);
        p.second = std::max(p.second, sr);
    }
    std::sort(a.begin(), a.end());
    std::vector<std::pair<int, int>> b;
    for (auto p : a) {
        while (!b.empty() && b.back().second >= p.second) { b.pop_back(); }
        b.push_back(p);
    }
    a = b;
    if (a.empty() || a.back().first < sl || sl == inf<int>) { out << "-1\n"; clear(); return; }
    ans = 1ll * sl * (inf<int> - sr);
    ans -= 1ll * a[0].first * (inf<int> - a[0].second);
    for (int i = 1; i < a.size(); i++) {
        ans -= 1ll * (a[i].first - a[i - 1].first) * (inf<int> - a[i].second);
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