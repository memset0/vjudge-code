#include <bits/stdc++.h>
#ifndef popteam
#define endl '\n'
#endif
#define all(x) begin(x), end(x)
using namespace std;
typedef std::vector<int> P;
const int MAXN = 3e5 + 11;
P res[MAXN];
void fail() {
    puts("NO");
    exit(0);
}
P solve(int n) // 1..2^k-1
{
    if (n == 1) return P{1};
    if (n == 2) fail();
    if (n == 3) return P{1, 3, 2};
    if (n == 7) return P{1, 3, 2, 6, 4, 5, 7};
    if (res[n].size()) return res[n];
    P &now = res[n];
    int m = n, k = -1;
    while (m)
        m >>= 1, ++k;
    int mid = 1 << k, rm = mid + (mid >> 1);
    if (n <= rm) fail();
    if (n + 1 == 2 * mid) {
        now = solve(n - 1);
        now.emplace_back(n);
        return now;
    }
    P f = solve(mid - 1), g = solve((mid >> 1) - 1);
    now = f;
    now.emplace_back(rm | 1);
    for (auto x : g) {
        now.emplace_back(x | mid);
        if ((x | rm) <= n && x != 1) now.emplace_back(x | rm);
    }
    now.emplace_back(rm), now.emplace_back(mid);
    return now;
}
void print(int x, int k) {
    int s[20];
    for (int i = 0; i < k; ++i)
        s[i] = x & 1, x >>= 1;
    for (int i = k - 1; i >= 0; --i)
        cout << s[i] ? '1' : ' ';
    // cout << char(s[i] + '0');
    cout << endl;
}
int main() {
#ifdef popteam
    // freopen("I.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;

    int m = n, k = 0;
    while (m)
        m >>= 1, ++k;
    // int mid = 1 << k, rm = mid + (mid >> 1);
    P f = solve(n);
    cout << "YES\n";
    for (auto x : f)
        cout << x << " ";
    // cout << "See:\n";
    // for (auto x : f)
    //     print(x, k);
    return 0;
}