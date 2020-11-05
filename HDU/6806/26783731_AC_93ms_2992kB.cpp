#include <bits/stdc++.h>

const int mod = 1e9 + 7;

const int N = 1e6 + 5;

int T, n;
long long a[N], f[N];

long long get(std::string str) {
    long long res = 0;
    for (auto x : str) {
        res = res * 27 + x - 'a' + 1;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    for (std::cin >> T; T; T--) {
        std::cin >> n;
        for (int i = 0; i < n; i++) {
            std::string str;
            std::cin >> str;
            a[i] = get(str);
            if (i >= 2 && a[i] == a[i - 1] && a[i] == a[i - 2]) {
                n--; i--;
            }
        }
        f[n] = 1;
        for (int i = n - 1; i >= 0; i--) {
            f[i] = f[i + 1];
            if (i + 2 <= n && a[i] != a[i + 1]) {
                f[i] = (f[i] + f[i + 2]) % mod;
            }
        }
        printf("%d\n", f[0]);
    }
    return 0;
}