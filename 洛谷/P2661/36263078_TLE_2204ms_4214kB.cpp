// luogu-judger-enable-o2
//一般模拟 80分TLE 

#include <bits/stdc++.h> 
using namespace std;
const int maxn = 200010;
int n, ans, a[maxn], val[maxn], pos[maxn];
int main() {
    memset(val, 0, sizeof(val));
    cin >> n;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    ans = n + 1;
    int i, j, k;
    for (i = 1; i <= n; i++) {
        if (val[i]) continue;
        memset(pos, 0, sizeof(pos));
        k = pos[i] = 1;
        for (j = a[i]; pos[j] != -1; j = a[j]) {
            k++;
            if (pos[j]) {
                val[j] = k - pos[j];
                pos[j] = -1;
            } else {
                pos[j] = k;
            }
        }
    }
    for (int i = 1; i <= n; i++)
        if (val[i] != 0 && val[i] < ans) ans = val[i];
    cout << ans << endl;
    return 0;
}
