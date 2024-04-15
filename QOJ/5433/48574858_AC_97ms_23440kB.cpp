#include <bits/stdc++.h>
#define all(x) begin(x), end(x)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 400011;
double pre[MAXN], suf[MAXN];
int fx[MAXN], diff;
int ca[MAXN], cb[MAXN];
ll pl[MAXN], sl[MAXN];
pii a[MAXN], b[MAXN];
int place(int val) { return std::lower_bound(fx + 1, fx + diff + 1, val) - fx; }
void points(int n, int m) {
    fprintf(stderr, "De:points %d %d\n", n, m);
    for (int i = 1; i <= n; ++i) {
        int l = place(a[i].first), r = place(a[i].second);
        ++ca[l], --ca[r + 1];
    }
    for (int i = 1; i <= m; ++i) {
        int l = place(b[i].first), r = place(b[i].second);
        ++cb[l], --cb[r + 1];
    }
    int la = 0;
    for (int i = 1; i <= diff; ++i) {
        ca[i] += ca[i - 1];
        cb[i] += cb[i - 1];
        if (cb[i])
            pre[i] = pre[i - 1] + fx[i], pl[i] = pl[i - 1] + 1;
        else
            pre[i] = pre[i - 1], pl[i] = pl[i - 1];
    }
    for (int i = diff; i; --i)
        if (cb[i])
            suf[i] = suf[i + 1] + fx[i], sl[i] = sl[i + 1] + 1;
        else
            suf[i] = suf[i + 1], sl[i] = sl[i + 1];
    double ans = 0;
    for (int i = 1; i <= diff; ++i)
        if (ca[i]) ans += (pl[i - 1] * fx[i] - pre[i - 1]) + (suf[i + 1] - sl[i + 1] * fx[i]);
    printf("%.10lf\n", ans / n / m);
}
void range_point(int n, int m) {
    fprintf(stderr, "De:Range_point %d %d\n", n, m);
    for (int i = 1; i <= n; ++i) {
        int l = place(a[i].first), r = place(a[i].second);
        ++ca[l], --ca[r];
    }
    for (int i = 1; i <= m; ++i) {
        int l = place(b[i].first), r = place(b[i].second);
        ++cb[l], --cb[r + 1];
    }
    int la = 0;
    for (int i = 1; i <= diff; ++i) {
        ca[i] += ca[i - 1];
        cb[i] += cb[i - 1];
        if (ca[i]) la += fx[i + 1] - fx[i];
        if (cb[i])
            pre[i] = pre[i - 1] + fx[i], pl[i] = pl[i - 1] + 1;
        else
            pre[i] = pre[i - 1], pl[i] = pl[i - 1];
    }
    for (int i = diff; i; --i)
        if (cb[i])
            suf[i] = suf[i + 1] + fx[i], sl[i] = sl[i + 1] + 1;
        else
            suf[i] = suf[i + 1], sl[i] = sl[i + 1];
    double ans = 0;
    for (int i = 1; i <= diff; ++i)
        if (ca[i]) {
            double mid = double(fx[i] + fx[i + 1]) / 2;
            double now = (pl[i] * mid - pre[i]) + (suf[i + 1] - sl[i + 1] * mid);
            ans += now * (fx[i + 1] - fx[i]);
        }
    printf("%.10lf\n", ans / la / pl[diff]);
}
int main() {
#ifdef popteam
    freopen("A.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    int n, m, flag1 = 1, flag2 = 1;
    diff = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {

        cin >> a[i].first >> a[i].second, fx[++diff] = a[i].first, fx[++diff] = a[i].second;
        if (a[i].first < a[i].second) flag1 = 0;
    }
    for (int i = 1; i <= m; ++i) {
        cin >> b[i].first >> b[i].second, fx[++diff] = b[i].first, fx[++diff] = b[i].second;
        if (b[i].first < b[i].second) flag2 = 0;
    }
    sort(fx + 1, fx + diff + 1), diff = unique(fx + 1, fx + diff + 1) - fx - 1;
    if (flag1 && flag2) {
        points(n, m);
        return 0;
    }
    if (!flag1 && flag2) {
        range_point(n, m);
        return 0;
    }
    if (flag1 && !flag2) {
        swap(a, b), swap(n, m);
        range_point(n, m);
        return 0;
    }
    fprintf(stderr, "De:Normal\n");
    for (int i = 1; i <= n; ++i) {
        int l = place(a[i].first), r = place(a[i].second);
        ++ca[l], --ca[r];
    }
    for (int i = 1; i <= m; ++i) {
        int l = place(b[i].first), r = place(b[i].second);
        ++cb[l], --cb[r];
    }
    double sum = 0, ans = 0, la = 0, lb = 0;
    for (int i = 1; i <= diff; ++i) {
        // printf("i=%d(%d)\n", i, fx[i]);
        ca[i] += ca[i - 1];
        if (ca[i]) la += fx[i + 1] - fx[i];
        cb[i] += cb[i - 1];
        // printf("ca=%d,cb=%d\n", ca[i], cb[i]);
        if (cb[i]) {
            lb += fx[i + 1] - fx[i];
            pre[i] = pre[i - 1] + double(fx[i + 1] + fx[i]) / 2.0 * (fx[i + 1] - fx[i]);
            pl[i] = pl[i - 1] + fx[i + 1] - fx[i];
        } else
            pre[i] = pre[i - 1], pl[i] = pl[i - 1];
    }
    // printf("la=%.2lf,lb=%.2lf\n", la, lb);
    for (int i = diff; i; --i)
        if (cb[i]) {
            suf[i] = suf[i + 1] + double(fx[i + 1] + fx[i]) / 2.0 * (fx[i + 1] - fx[i]);
            sl[i] = sl[i + 1] + (fx[i + 1] - fx[i]);
        } else
            suf[i] = suf[i + 1], sl[i] = sl[i + 1];

    for (int i = 1; i <= diff; ++i)
        if (ca[i]) {
            double l = fx[i + 1] - fx[i];
            double mid = double(fx[i] + fx[i + 1]) / 2.0;
            double fa = l / la * (pl[i - 1] * mid - pre[i - 1]);
            double fb = l / la * l / lb * (l / 3.0);
            double fc = l / la * (suf[i + 1] - sl[i + 1] * mid);
            // printf("[%d,%d] %.2lf %.2lf %.2lf\n", fx[i], fx[i + 1], fa, fb, fc);
            ans += l / la * (pl[i - 1] * mid - pre[i - 1]) / lb;
            if (cb[i]) ans += l / la * l / lb * (l / 3.0);
            ans += l / la * (suf[i + 1] - sl[i + 1] * mid) / lb;
        }
    printf("%.10lf\n", ans);
    return 0;
}