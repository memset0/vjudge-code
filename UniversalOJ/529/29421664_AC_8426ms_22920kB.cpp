#include <bits/stdc++.h>

const int N = 1e6 + 5;

int T, n, m, ans[N][6];
char str[N];
std::set<int> f, g;
std::set<std::pair<int, int>> h;

int main() {
    for (scanf("%d", &T); T; T--) {
        scanf("%s", str);
        n = strlen(str); m = n / 6;
        f.clear(); g.clear();
        for (int i = 0; i < n; i++) {
            if (str[i] == '1') { f.insert(i); }
            if (str[i] == '5') { g.insert(i); }
        }
        h.clear();
        for (int i = n - 1, j; i >= 0; i--) {
            if (str[i] == '4') {
                std::set<int>::iterator it = f.lower_bound(i);
                j = *(--it);
                f.erase(j);
                h.insert({j + 1, i + 1});
            }
        }
        for (int i = 0; i < m; i++) {
            int x = *f.begin(); x++;
            int y = *g.begin(); y++;
            ans[i][0] = x;
            std::set<std::pair<int, int>>::iterator it = h.lower_bound({x, 0});
            ans[i][1] = it->first;
            ans[i][2] = it->second;
            ans[i][3] = y;
            f.erase(f.begin());
            g.erase(g.begin());
            h.erase(it);
        }
        for (int i = 0; i < m; i++) {
            ans[i][4] = h.begin()->first;
            ans[i][5] = h.begin()->second;
            h.erase(h.begin());
            printf("%d %d %d %d %d %d\n", ans[i][0], ans[i][1], ans[i][2], ans[i][3], ans[i][4], ans[i][5]);
        }
    }
    return 0;
}