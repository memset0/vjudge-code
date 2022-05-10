#include <bits/stdc++.h>
using namespace std;
int a[30000], f[3000], e[1000];
bool cmp(int x, int y) {
    return a[x] == a[y] ? x < y : a[x] > a[y];
}
int main(){
    int i, j, k, n;
    cin >> n >> k;
    for(i = 1; i <= 10; i++) cin >> e[i];
    for(i = 1; i <= n; i++) cin >> a[i], f[i] = i;
    sort(f + 1, f + n + 1, cmp);
    for(i = 1; i <= n; i++) a[f[i]] += e[(i - 1) % 10 + 1]; 
    sort(f + 1, f + n + 1, cmp);
    for(i = 1; i <= k; i++) cout << f[i] << " ";
    return 0;
}