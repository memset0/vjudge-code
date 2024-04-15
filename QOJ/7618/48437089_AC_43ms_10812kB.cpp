#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
const int N = 2e6;
int T, n, m, ts[30], tt[30], TIM1, TIM2;
int l, r, mid;
int mx, nm, an[N + 10], vis1[N + 10], vis2[N + 20];
string s, t;
void Ins(int x) {
    if (vis1[x] != TIM1) vis1[x] = TIM1, an[x] = 0;
    if (vis2[x] == TIM2) return;
    vis2[x] = TIM2;
    if ((++an[x]) > mx) mx = an[x];
}
bool Check(int x) {
    // cout << "CHECK " << x << "\n";
    int lm, tl, tr, tmp;
    ++TIM1;
    mx = nm = 0;
    for (int i = 0; i < 26 && nm == mx; ++i)
        if (tt[i]) {
            // cout << "i=" << i << "\n";
            ++nm;
            lm = ts[i] / x;
            // cout << "LM=" << lm << "\n";
            tl = 1;
            ++TIM2;
            while (tl <= lm && tl <= tt[i]) {
                tr = tt[i] / (tmp = tt[i] / tl);
                if (tr <= lm && tt[i] % tr == 0)
                    Ins(tmp - 1), Ins(tmp);
                else
                    Ins(tmp);
                tl = tr + 1;
            }
        }
    return nm == mx;
}
int main() {
#ifdef popteam
    freopen("M.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> T;
    while (T--) {
        cin >> s >> t;
        n = s.size(), m = t.size();
        for (int i = 0; i < 26; ++i)
            ts[i] = tt[i] = 0;
        for (int i = 0; i < n; ++i)
            ++ts[s[i] - 'a'];
        for (int i = 0; i < m; ++i)
            ++tt[t[i] - 'a'];
        l = 0, r = n;
        for (int i = 0; i < 26; ++i) {
            if (ts[i] < tt[i]) {
                cout << "0\n";
                goto Skip;
            }
            if (!tt[i]) continue;
            ts[i] -= tt[i];
            // cout << "TS " << i << "=" << ts[i] << "\n";
        }
        // cout << "DONE.l=" << l << " r=" << r << "\n";
        while (l < r) {
            mid = (l + r + 1 >> 1);
            if (Check(mid))
                l = mid;
            else
                r = mid - 1;
        }
        cout << l + 1 << "\n";
    Skip:;
    }
}