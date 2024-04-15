#include <bits/stdc++.h>
#define endl '\n'
#ifndef popteam
#define endl '\n'
#endif
#define all(x) begin(x), end(x)
using namespace std;
typedef long long ll;
const int N = 1e5 + 9;
int n, m, a[N], b[N], t[N], k[N], x[N], y[N];
long long sum;
struct segtree {
    struct segment {
        int l, r, mid;
        int pos, tag;
        long long res[4];
    } p[N << 2];
    int nod;
    vector<int> val, cnt;
    void pushup(int u, int v) {
        static long long tmp[4];
        memcpy(tmp, p[u].res, sizeof(long long) << 2);
        for (int i = 0; i < 4; i++)
            p[u].res[(i + v) & 3] = tmp[i];
        p[u].pos = (p[u].pos + v) & 3;
        p[u].tag = (p[u].tag + v) & 3;
    }
    void pushdown(int u) {
        if (p[u].tag) {
            pushup(u << 1, p[u].tag);
            pushup(u << 1 | 1, p[u].tag);
            p[u].tag = 0;
        }
    }
    void maintain(int u) {
        for (int i = 0; i < 4; i++)
            p[u].res[i] = p[u << 1].res[i] + p[u << 1 | 1].res[i];
    }
    void build(int u, int l, int r) {
        p[u].l = l, p[u].r = r, p[u].mid = (l + r) >> 1;
        if (l == r) return;
        build(u << 1, l, p[u].mid);
        build(u << 1 | 1, p[u].mid + 1, r);
    }
    void update(int u, int k, int x) {
        // fprintf(stderr, "update u=%d k=%d x=%d\n", u, k, x);
        if (p[u].l == p[u].r) {
            p[u].res[p[u].pos] += x;
            return;
        }
        pushdown(u);
        if (k <= p[u].mid) {
            update(u << 1, k, x);
        } else {
            update(u << 1 | 1, k, x);
        }
        maintain(u);
    }
    void modify(int u, int l, int r, int v) {
        if (p[u].l == l && p[u].r == r) {
            pushup(u, v);
            return;
        }
        pushdown(u);
        if (r <= p[u].mid) {
            modify(u << 1, l, r, v);
        } else if (l > p[u].mid) {
            modify(u << 1 | 1, l, r, v);
        } else {
            modify(u << 1, l, p[u].mid, v);
            modify(u << 1 | 1, p[u].mid + 1, r, v);
        }
        maintain(u);
    }
    void push(int x) {
        // fprintf(stderr, "push %d\n", x);
        val.push_back(x);
    }
    void init() {
        sort(all(val));
        cnt.resize(val.size());
        for (int l = 0, r = 0; l < val.size(); l = r + 1, r = l) {
            while (r + 1 < val.size() && val[r] == val[r + 1])
                ++r;
            cnt[l] += r - l + 1;
        }
        build(1, 1, val.size());
    }
    int locate(int x) {
        int k = lower_bound(all(val), x) - val.begin();
        // fprintf(stderr, "locate x=%d k=%d cnt=%d => %d \n", x, k, cnt[k], (int)val.size() - (k + cnt[k] - 1));
        k += --cnt[k];
        return (int)val.size() - k;
    }
    void insert(int k, int x) {
        ++nod;
        modify(1, k, val.size(), 1);
        update(1, k, x);
    }
    void erase(int k, int x) {
        --nod;
        modify(1, k, val.size(), 3);
        update(1, k, -x);
    }
    void query(long long *res) {
        if (nod) {
            memcpy(res, p[1].res, sizeof(long long) << 2);
        } else {
            memset(res, 0, sizeof(long long) << 2);
        }
    }
} bg, sm;
long long solve() {
    static long long tmp[4];
    long long ans = sum;
    bg.query(tmp);
    // fprintf(stderr, "bg :: %lld %lld %lld %lld\n", tmp[0], tmp[1], tmp[2], tmp[3]);
    ans += tmp[2] + tmp[3];
    sm.query(tmp);
    // fprintf(stderr, "sm :: %lld %lld %lld %lld\n", tmp[0], tmp[1], tmp[2], tmp[3]);
    if (bg.nod & 1) {
        ans += tmp[1] + tmp[3];
    } else {
        ans += tmp[0] + tmp[2];
    }
    return ans;
}
int main() {
#ifdef popteam
    freopen("I.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        (b[i] > a[i] ? bg : sm).push(b[i] - a[i]);
    }
    for (int i = 1; i <= m; i++) {
        cin >> k[i] >> x[i] >> y[i];
        (y[i] > x[i] ? bg : sm).push(y[i] - x[i]);
    }
    bg.init();
    sm.init();
    for (int i = 1; i <= n; i++) {
        sum += a[i];
        t[i] = (b[i] > a[i] ? bg : sm).locate(b[i] - a[i]);
        (b[i] > a[i] ? bg : sm).insert(t[i], b[i] - a[i]);
    }
    cout << solve() << endl;
    for (int j = 1; j <= m; j++) {
        int i = k[j];
        sum -= a[i];
        (b[i] > a[i] ? bg : sm).erase(t[i], b[i] - a[i]);
        a[i] = x[j], b[i] = y[j];
        sum += a[i];
        t[i] = (b[i] > a[i] ? bg : sm).locate(b[i] - a[i]);
        (b[i] > a[i] ? bg : sm).insert(t[i], b[i] - a[i]);
        cout << solve() << endl;
    }
}