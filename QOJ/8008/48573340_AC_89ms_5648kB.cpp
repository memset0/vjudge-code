#include <bits/stdc++.h>
#ifndef popteam
#define endl '\n'
#endif
#define all(x) begin(x), end(x)
using namespace std;
const int N = 1e5 + 9;
int n, x, k, a[N], dis[N], c[N];
long long s[N];
int main() {
#ifdef popteam
    freopen("F.in", "r", stdin);
#endif
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> x >> k;
    for (int i = 1; i <= k; i++) {
        cin >> a[i];
    }
    queue<int> q;
    memset(dis, -1, sizeof(dis));
    dis[0] = 0;
    q.push(0);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = 1; i <= k; i++) {
            int v = (u - a[i] + n) % n;
            if (dis[v] == -1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    for (int i = 0; i < n; i++)
        if (dis[i] != -1) {
            c[dis[i]]++;
            s[dis[i]] += dis[i];
        }
    for (int i = 1; i < n; i++) {
        c[i] += c[i - 1];
        s[i] += s[i - 1];
    }
    for (int k = 0; k < n; k++)
        if (k == n - 1 || (c[k] * k <= s[k] + n && s[k] + n <= c[k] * (k + 1))) {
            long long p = s[k] + n, q = c[k];
            long long g = __gcd(p, q);
            if (dis[x] <= k && dis[x] != -1) {
                cout << dis[x] << " " << 1 << endl;
            } else {
                cout << (p / g) << " " << (q / g) << endl;
            }
            return 0;
        }
}