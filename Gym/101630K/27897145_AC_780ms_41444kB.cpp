// =================================
//   author: memset0
//   date: 2019.02.13 17:11:20
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
namespace ringo {
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
template <class T> inline void print(T x, char c) { print(x), putchar(c); }
 
const int N = 100;
int n, l, flag;
ull r, blk, sum, ned, ans, a[N], b[N];
std::unordered_map <ull, int> map;
 
inline ull fpow(ull a, ull b) {
    ull s = 1;
    for (; b; b >>= 1, a = a * a) if (b & 1) s = s * a;
    return s;
}
 
inline ull inv(ull a, int l) {
    ull ans = fpow(a >> l, (1ull << (63 - l)) - 1);
    return l ? ans % (1ull << (64 - l)) : ans;
}
 
void main() {
    read(n);
    for (int i = 1; i <= n; i++) read(b[i]);
    read(ned);
    if (n <= 40) {
        int l_n = n >> 1, r_n = n - l_n;
        for (int x = 0; x < (1 << l_n); x++) {
            sum = 0;
            for (int i = 1; i <= l_n; i++)
                if ((x >> (i - 1)) & 1)
                    sum += b[i];
            map[ned - sum] = x;
        }
        for (int x = 0; x < (1 << r_n); x++) {
            sum = 0;
            for (int i = 1; i <= r_n; i++)
                if ((x >> (i - 1)) & 1)
                    sum += b[l_n + i];
            if (map.find(sum) != map.end()) {
                int y = map[sum];
                for (int i = 1; i <= l_n; i++) putchar('0' + (y >> (i - 1) & 1));
                for (int i = 1; i <= r_n; i++) putchar('0' + (x >> (i - 1) & 1));
                putchar('\n'); return;
            }
        }
    } else {
        while (b[1] % (1ull << (l + 1)) == 0) ++l;
        ull mod = 1ull << (64 - l);
        for (a[1] = 1ull << l; ; a[1] += 1ull << (l + 1)) {
            r = (b[1] >> l) * inv(a[1], l), r = l ? r % mod : r;
            for (int i = 0; i < (1 << l); i++) {
                ull inv_r = inv(r, 0);
                // printf("r = %llu mod = %llu inv_r = %llu\n", r, mod, inv_r);
                for (int i = 2; i <= n; i++) a[i] = b[i] * inv_r;
                // for (int i = 1; i <= n; i++) print(a[i], " \n"[i == n]);
                sum = 0, flag = 1;
                for (int i = 1; i <= n && flag; i++) {
                    // printf("> %llu %llu %llu : %d\n", a[i], sum, a[i] + sum, a[i] >= sum);
                    flag &= a[i] >= sum && a[i] + sum > sum, sum += a[i];
                }
                if (flag) {
                    sum = ned * inv(r, 0);
                    for (int i = n; i; i--) if (sum >= a[i]) sum -= a[i], ans |= 1ull << (i - 1);
                    for (int i = 1; i <= n; i++) putchar(48 + ((ans >> (i - 1)) & 1));
                    putchar('\n'); return;
                } r += mod;
            }
        }
    }
}
 
} signed main() { return ringo::main(), 0; }
/**************************************************************
    Problem: 5218
    User: w15
    Language: C++
    Result: 正确
    Time:1168 ms
    Memory:30232 kb
****************************************************************/