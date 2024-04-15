#include <bits/stdc++.h>
using namespace std;
using ll = __int128;
using lf = long double;
const int N = 3e5 + 9, mod = 998244353, i2 = mod + 1 >> 1;
const ll INF = 1e13;
struct line {
    ll k, b;
    ll F(ll x) { return k * x + b; }
} l1[N + 10], l2[N + 10];
bool cov(line l1, line l2, line l3) { return (l2.b - l1.b) * (l1.k - l3.k) >= (l3.b - l1.b) * (l1.k - l2.k); }
/*bool cov2(line l1, line l2, line l3) {
    return (l2.b - l1.b) * (l1.k - l3.k) <= (l3.b - l1.b) * (l1.k - l2.k);
}*/
int n, s1, s2, n1, n2, t1, t2, ans;
ll l[N + 10], r[N + 10], nl, nr, np, tl, tr;
long long tmpl, tmpr;
void Ins(int &sz, line *li, line x) {
    if (!sz) return (void)(li[sz = 1] = x);
    while (sz > 1 && cov(x, li[sz - 1], li[sz]))
        --sz;
    li[++sz] = x;
}
ll CalcF(line a, line b) {
    ll p = b.b - a.b, q = a.k - b.k;
    if (q * (p / q) == p) return p / q;
    if ((p < 0) ^ (q < 0)) return p / q - 1;
    return p / q;
}
ll CalcC(line a, line b) {
    ll p = b.b - a.b, q = a.k - b.k;
    if (q * (p / q) == p) return p / q;
    if ((p < 0) ^ (q < 0)) return p / q;
    return p / q + 1;
}
ll Sum(ll lv, ll rv, ll tn) { return (lv + rv) % mod * tn % mod * i2 % mod; }
int main() {
#ifdef popteam
    freopen("K.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> tmpl, l[i] = tmpl;
    for (int i = 1; i <= n; ++i)
        cin >> tmpr, r[i] = tmpr;
    for (int i = 1; i <= n; ++i)
        Ins(s1, l1, (line){1 - i, r[i]});
    for (int i = n; i >= 1; --i)
        Ins(s2, l2, (line){1 - i, l[i]});
    /*
    cout << "L1:\n";
    for (int i = 1; i <= s1; ++i)
        cout << l1[i].k << "x + " << l1[i].b << "\n";
    cout << "L2:\n";
    for (int i = 1; i <= s2; ++i)
        cout << l2[i].k << "x + " << l2[i].b << "\n";
    */
    nl = -INF;
    n1 = 1, n2 = 1;
    while (n1 <= s1 && n2 <= s2) {
        t1 = n1, t2 = n2;
        // if (n1 < s1) cout << "F1 " << CalcF(l1[n1], l1[n1 + 1]) << "\n";
        // if (n2 < s2) cout << "F2 " << CalcF(l2[n2], l2[n2 + 1]) << "\n";
        if (n1 == s1 && n2 == s2)
            nr = INF, ++n1;
        else if (n1 < s1 && (n2 == s2 || CalcF(l1[n1], l1[n1 + 1]) < CalcF(l2[n2], l2[n2 + 1])))
            nr = CalcF(l1[n1], l1[n1 + 1]), ++n1;
        else
            nr = CalcF(l2[n2], l2[n2 + 1]), ++n2;
        if (nl > nr) continue;
        // cout << "T1=" << t1 << " T2=" << t2 << " nl=" << nl << ",nr=" << nr << "\n";
        if (l1[t1].k == l2[t2].k) {
            ans = (ans + (nr - nl + 1) % mod * ((l1[t1].b - l2[t2].b + 1) % mod)) % mod;
            // cout << "ANS=" << ans << "\n";
        } else {
            if (l1[t1].k < l2[t2].k)
                tr = min(nr, CalcF(l1[t1], l2[t2])), tl = nl;
            else
                tl = max(nl, CalcC(l1[t1], l2[t2])), tr = nr;
            if (tl <= tr) {
                // cout << "TL=" << tl << " tr=" << tr << "\n";
                ans = (ans + Sum(l1[t1].F(tl), l1[t1].F(tr), tr - tl + 1) - Sum(l2[t2].F(tl) - 1, l2[t2].F(tr) - 1, tr - tl + 1) + mod) % mod;
                // cout << "ANS=" << ans << "\n";
            }
        }
        nl = nr + 1;
    }
    cout << (ans + mod) % mod << "\n";
}