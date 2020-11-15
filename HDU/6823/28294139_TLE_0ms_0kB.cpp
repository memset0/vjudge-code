#include <bits/stdc++.h>

inline long long read() {
    char c, _c; long long x; for (c = _c = getchar(); !isdigit(c); c = getchar()) { _c = c; }
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return _c == '-' ? -x : x;
}

const int N = 1e6 + 5, L = 61;

int n, m, basen, bsn;
long long base[L], bs[L];

void insert(long long x) {
    for (int i = L - 1; i >= 0; i--) {
        if (x >> i & 1) {
            if (base[i] == 0) {
                basen++;
                base[i] = x;
                break;
            }
            x ^= base[i];
        }
    }
}
long long query(long long x) {
    long long res = 0;
    for (int i = L - 1; i >= 0; i--) {
        if (x >> i & 1) {
            if (base[i] == 0) {
                continue;
            }
            res = res * 2 + 1;
            x ^= base[i];
        } else {
            if (base[i] == 0) {
                continue;
            }
            res = res * 2;
        }
    }
    if (x != 0) { return -1; }
    return res;
}
 
void _insert(long long x) {
    for (int i = L - 1; i >= 0; i--) {
        if (x >> i & 1) {
            if (bs[i] == 0) {
                bsn++;
                bs[i] = x;
                break;
            }
            x ^= bs[i];
        }
    }
}
long long _query(long long x) {
    for (int i = L - 1; i >= 0; i--) {
        x = std::max(x, x ^ bs[i]);
    }
    return x;
}

void solveConstruct() {
    if (basen % 2 == 1) { 
        printf("NoSolution\n");
        m = read();
        for (int i = 0; i < m; i++) { read(); }
        return;
    }
    printf("HaveSolution\n");
    m = read();
    for (int i = 0; i < m; i++) {
        long long x = read();
        long long res = query(x);
        if (res == -1) { printf("-1\n"); continue; }
        long long p = res >> (basen / 2);
        long long ans = 0;
        for (int j = 0, k = 0; j < L; j++) {
            if (base[j] > 0) {
                if (p >> k & 1) {
                    ans ^= base[j];
                }
                k++;
            }
        }
        printf("%lld\n", ans);
    }
}

void solveCheck() {
    char str[15];
    scanf("%s", str);
    if (basen % 2 == 0 && str[0] == 'N') {
        printf("No\n"); return;
    }
    if (str[0] == 'N') {
        printf("Yes\n"); return;
    }
    if (basen % 2 == 1 && str[0] == 'H') {
        m = read();
        for (int i = 0; i < m; i++) { read(); read(); }
        printf("No\n"); return;
    }
    m = read();
    bool ok = true;
    std::vector<std::pair<long long, long long>> e;
    e.push_back({0, 0});
    for (int i = 0; i < m; i++) {
        long long x = read(), y = read();
        if (!ok) { continue; }
        long long res = query(x);
        if (res == -1 && y != -1) { ok = false; continue; }
        if (res != -1 && y == -1) { ok = false; continue; }
        if (y == -1) { continue; }
        e.push_back({x, y});
        e.push_back({y, 0});
    }
    if (ok) {
        std::sort(e.begin(), e.end());
        bsn = 0;
        for (int i = 0; i < L; i++) { bs[i] = 0; }
        std::map<long long, long long> f;
        for (auto i : e) {
            if (i.second == 0) { _insert(i.first); }
            if (f.count(i.second)) {
                _insert(f[i.second] ^ i.first);
            }
            f[i.second] = i.first;
        }
        if (bsn > basen / 2) { ok = false; } else {
            std::map<long long, long long> g;
            std::set<long long> set;
            for (auto i : e) {
                if (g.count(i.second)) {
                    if (g[i.second] != _query(i.first)) {
                        ok = false; break;
                    }
                } else {
                    long long res = _query(i.first);
                    if (set.count(res)) {
                        ok = false; break;
                    }
                    set.insert(res);
                    g[i.second] = res;
                }
            }
        }
    }
    printf("%s\n", ok ? "Yes" : "No");
}

int main() {
    for (int T = read(); T; T--) {
        n = read(); basen = 0;
        for (int i = 0; i < L; i++) {
            base[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            long long x = read();
            insert(x);
        }
        char opt[15];
        scanf("%s", opt);
        if (opt[1] == 'o') {
            solveConstruct();
        } else {
            solveCheck();
        }
    }
    return 0;
}
