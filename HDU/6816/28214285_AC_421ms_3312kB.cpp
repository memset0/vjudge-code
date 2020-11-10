#include <bits/stdc++.h>

inline int read() {
    char c; int x; for (c = getchar(); !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); c = getchar()) { x = x * 10 + c - '0'; } return x;
}

const int N = 205, K = 12;

int n, k, c[N];
std::vector<int> ans, p, a[K], d[N];

int main() {
    a[0].push_back(0);
    a[0].push_back(1);
    for (int k = 1; k < K; k++) {
        std::vector<int> b0 = a[k - 1], b1 = a[k - 1];
        for (int i = 0; i < (1 << k); i++) {
            b0[i] *= 2; b1[i] *= 2; b0[i]++;
            if (b0[i] / 2 & 1) { std::swap(b0[i], b1[i]); }
        }
        std::reverse(b0.begin(), b0.end());
        for (auto x : b0) { a[k].push_back(x); }
        for (auto x : b1) { a[k].push_back(x); }
    }
    for (int T = read(); T; T--) {
        n = read(); k = read(); k--;
        std::vector<int> f;
        for (int i = n - 1; i >= 0; i--) { f.push_back(i); }
        for (int i = 0; i < n; i++) { f.push_back(i); }
        for (int i = 0; i < k; i++) {
            std::vector<int> _f = f;
            for (auto x : _f) { f.push_back(x); }
        }
        for (int i = 0; i < n; i++) { c[i] = 0; d[i].resize(1 << k + 1); }
        int id = 0;
        for (auto i : f) {
            d[i][a[k][c[i]++]] = id++;
        }
        ans.clear();
        for (int i = 0; i < n; i++) {
            int ii = 0;
            for (auto x : d[i]) {
                int y = x + 1;
                if (ii & 1) {
                    ans.push_back(y * 2 - 1);
                } else {
                    ans.push_back(y * 2);
                }
                ii++;
            }
            ii = 0;
            for (auto x : d[i]) {
                int y = x + 1;
                if (ii & 1) {
                    ans.push_back(y * 2);
                } else {
                    ans.push_back(y * 2 - 1);
                }
                ii++;
            }
        }
        p.clear();
        for (int i = 0; i < ans.size(); i++) {
            p.push_back(read());
        }
        bool flag = false;
        for (int i = 0; i < ans.size(); i++) {
            if (flag) { printf(" "); }
            printf("%d", p[ans[i] - 1]);
            flag = true;
        }
        printf("\n");
    }
    return 0;
}
