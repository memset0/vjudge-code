#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define per(i, a, b) for (int i = a; i >= b; i--)

using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') { fu = -1; } c = getchar(); }
    while (c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

const int N = 2e5 + 5;

vector <pii> adj[N];
pair <ll, ll> cat[N];
ll f[N][2], ans;
int T, n, k;

bool cmp(pair <ll, ll> a, pair <ll, ll> b) { return a.first > b.first; }

void dfs1(int u, int fa) {
    for (int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i].first;
        if (v == fa) continue;
        dfs1(v, u);
    }
    int len = 0;
    for (int i = 0; i < (int)adj[u].size(); i++) {
        int v = adj[u][i].first;
        if (v == fa) continue;
        cat[++len] = make_pair(f[v][0] + adj[u][i].second, f[v][1] + adj[u][i].second);
    }
    sort(cat + 1, cat + len + 1, cmp);
    ll sum = 0;
    for (int i = 1; i <= min(k - 1, len); i++) sum += cat[i].first;
    f[u][0] = sum;
    for (int i = k; i <= len; i++) sum += cat[i].first;
    f[u][1] = sum; ans = max(ans, sum);
    sum = 0;
    for (int i = 1; i <= min(k, len); i++) sum += cat[i].first;
    for (int i = 1; i <= min(k, len); i++) ans = max(ans, sum - cat[i].first + cat[i].second);
    for (int i = k + 1; i <= len; i++) ans = max(ans, sum - cat[k].first + cat[i].second);
    if (k == 1) return;
    sum = 0;
    for (int i = 1; i <= min(k - 1, len); i++) sum += cat[i].first;
    for (int i = 1; i <= min(k - 1, len); i++) f[u][1] = max(f[u][1], sum - cat[i].first + cat[i].second);
    for (int i = k; i <= len; i++) f[u][1] = max(f[u][1], sum - cat[k - 1].first + cat[i].second);
}

int main() {
    read(T);
    while (T--) {
        read(n); read(k); ans = 0;
        for (int i = 1; i <= n; i++) adj[i].clear();
        for (int i = 1; i < n; i++) {
            int u, v, w;
            read(u); read(v); read(w);
            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
        }
        if (k == 0) {
            print(0, '\n');
            continue;
        }
        dfs1(1, 0);
        print(ans, '\n');
    }
    return 0;
}
