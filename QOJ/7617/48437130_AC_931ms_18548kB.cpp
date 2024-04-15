#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
#define pi pair<ll, int>
#define seg pair<int, int>
#define f first
#define s second
using namespace std;
typedef long long ll;
const int N = 2e5;
int n, nw, ans;
ll a[N + 10], prt[N + 10];
pi ar[N + 10];
set<seg> s;
void Del(int x) {
    set<seg>::iterator it = s.lower_bound((seg){x + 1, x + 1});
    --it;
    seg tmp = *it;
    ans -= (tmp.s - tmp.f + 1 >> 1), ans += (x - tmp.f + 1 >> 1) + (tmp.s - x >> 1);
    s.erase(it);
    s.insert((seg){tmp.f, x}), s.insert((seg){x + 1, tmp.s});
}
void Ins(int x) {
    set<seg>::iterator it = s.lower_bound((seg){x + 1, x + 1}), i2;
    i2 = it, --it;
    ans -= ((*it).s - (*it).f + 1 >> 1) + ((*i2).s - (*i2).f + 1 >> 1);
    seg tmp = (seg){(*it).f, (*i2).s};
    ans += (tmp.s - tmp.f + 1 >> 1);
    s.erase(i2), s.erase(it);
    s.insert(tmp);
}
void Solve(ll lv, ll rv, int l, int r) {
    if (l > r) return;
    if (lv == rv) {
        for (int i = l; i <= r; ++i)
            prt[i] = ar[lv].f;
        return;
    }
    ll mid = (lv + rv >> 1);
    // cout << "MID=" << mid << "\n";
    while (nw < mid)
        Ins(ar[++nw].s);
    while (nw > mid)
        Del(ar[nw--].s);
    // cout << "ANs=" << ans << "\n";
    int tans = ans;
    Solve(lv, mid, l, tans), Solve(mid + 1, rv, tans + 1, r);
}
int main() {
#ifdef popteam
    freopen("L.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    for (int i = 1; i < n; ++i)
        ar[i] = (pi){a[i + 1] - a[i], i};
    sort(ar + 1, ar + n);
    nw = 0;
    for (int i = 1; i <= n; ++i)
        s.insert((seg){i, i});
    Solve(1, n - 1, 1, n >> 1);
    for (int i = 1; i <= (n >> 1); ++i)
        cout << prt[i] << " \n"[i == (n >> 1)];
}