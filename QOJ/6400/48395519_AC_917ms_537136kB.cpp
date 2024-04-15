#include <bits/stdc++.h>
#ifndef popteam
#define endl '\n'
#endif
#define all(x) begin(x), end(x)
using namespace std;
using ull = unsigned long long;
const int N = 1e6 + 9;
int T, n, xl, xr, nod, x[N], a[N], cnt[N];
vector<int> hsh[N];
vector<int> tmp;
mt19937_64 rng(20040129);
// struct sequence {
//     vector<int> v;
//     bool empty() { return v.empty(); }
//     void reset() { v.clear(); }
//     bool operator>(const sequence &rhs) const {
//         for (size_t i = 0; i < v.size() && i < rhs.v.size(); i++)
//             if (v[i] != rhs.v[i]) {
//                 return v[i] > rhs.v[i];
//             }
//         return v.size() > rhs.v.size();
//     }
//     sequence insert(int x) {
//         sequence it = *this;
//         it.v.push_back(x);
//         sort(all(it.v), [&](int x, int y) { return x > y; });
//         return it;
//     }
// } f[N];
struct node {
    int lc, rc, cnt;
    ull hsh;
} e[N * 22];
void maintain(int u) {
    e[u].cnt = 0;
    e[u].hsh = 0;
    if (e[u].lc) {
        e[u].cnt += e[e[u].lc].cnt;
        e[u].hsh ^= e[e[u].lc].hsh;
    }
    if (e[u].rc) {
        e[u].cnt += e[e[u].rc].cnt;
        e[u].hsh ^= e[e[u].rc].hsh;
    }
}
void insert(int &u, int v, int k, int l, int r) {
    u = ++nod;
    // fprintf(stderr, "insert %d %d %d %d %d\n", u, v, k, l, r);
    if (l == r) {
        e[u].cnt = (v ? e[v].cnt : 0) + 1;
        e[u].hsh = hsh[l][e[u].cnt];
        return;
    }
    int mid = (l + r) >> 1;
    if (k <= mid) {
        e[u].rc = e[v].rc;
        insert(e[u].lc, e[v].lc, k, l, mid);
    } else {
        e[u].lc = e[v].lc;
        insert(e[u].rc, e[v].rc, k, mid + 1, r);
    }
    maintain(u);
    // fprintf(stderr, "end insert %d[%d %llu]\n", u, e[u].cnt, e[u].hsh);
}
bool cmp(int u, int v, int l, int r) {
    if (!u || !v) {
        return u < v;
    }
    if (l == r) {
        return e[u].cnt < e[v].cnt;
    }
    int mid = (l + r) >> 1;
    if (e[e[u].rc].hsh != e[e[v].rc].hsh) {
        return cmp(e[u].rc, e[v].rc, mid + 1, r);
    } else {
        return cmp(e[u].lc, e[v].lc, l, mid);
    }
}
void dfs(int u, vector<int> &ans, int l, int r) {
    // fprintf(stderr, "dfs %d[%d %llu] %d %d %d\n", u, e[u].cnt, e[u].hsh, (int)ans.size(), l, r);
    if (!u || !e[u].cnt) return;
    if (l == r) {
        for (int _ = e[u].cnt; _--;) {
            ans.push_back(l);
        }
        return;
    }
    int mid = (l + r) >> 1;
    dfs(e[u].rc, ans, mid + 1, r);
    dfs(e[u].lc, ans, l, mid);
}
struct sequence {
    int rt;
    bool empty() { return rt == 0; }
    void reset() { rt = 0; }
    bool operator>(const sequence &rhs) const { return cmp(rhs.rt, rt, 1, tmp.size()); }
    sequence insert(int x) {
        // fprintf(stderr, "insert x=%d\n", x);
        sequence res = *this;
        ::insert(res.rt, rt, x, 1, tmp.size());
        return res;
    }
} f[N];
deque<pair<int, sequence>> q;
int main() {
#ifdef popteam
    freopen("G.in", "r", stdin);
    // freopen("G.out", "w", stdout);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> T;
    while (T--) {
        nod = 0;
        cin >> n >> xl >> xr;
        for (int i = 1; i <= n; i++)
            cin >> x[i];
        tmp.clear();
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            tmp.push_back(a[i]);
        }
        sort(all(tmp));
        tmp.erase(unique(all(tmp)), tmp.end());
        fill_n(cnt + 1, tmp.size(), 0);
        for (int i = 1; i <= n; i++) {
            a[i] = lower_bound(all(tmp), a[i]) - tmp.begin() + 1;
            cnt[a[i]]++;
        }
        // for (int i = 1; i <= n; i++)
        //     cerr << a[i] << " \n"[i == n];
        for (int i = 1; i <= tmp.size(); i++) {
            while (hsh[i].size() <= cnt[i]) {
                hsh[i].push_back(rng());
            }
        }
        q.clear();
        int j = 1;
        for (int i = 1; i <= n; i++) {
            while (j < i && x[j] + xl <= x[i]) {
                if (!f[j].empty()) {
                    while (q.size() && f[j] > q.back().second) {
                        q.pop_back();
                    }
                    q.push_back(make_pair(j, f[j]));
                }
                j++;
            }
            while (q.size() && x[q.front().first] + xr < x[i]) {
                q.pop_front();
            }
            // fprintf(stderr, "i=%d :: ", i);
            // for (auto x : q)
            //     cerr << x.first << " ";
            // cerr << endl;
            if (q.size()) {
                f[i] = q.front().second.insert(a[i]);
            } else {
                f[i].reset();
                if (i == 1) {
                    f[i] = f[i].insert(a[1]);
                }
            }
        }
        if (f[n].empty()) {
            cout << -1 << endl;
        } else {
            vector<int> ans;
            dfs(f[n].rt, ans, 1, tmp.size());
            cout << ans.size() << endl;
            for (int i = 0; i < ans.size(); i++) {
                cout << tmp[ans[i] - 1] << " \n"[i + 1 == ans.size()];
            }
        }
    }
}