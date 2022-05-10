#include <bits/stdc++.h>
using namespace std;
long long t, n, f[50005], sum;
struct Node {
    long long a, b;
} a[50005];
bool cmp(Node x, Node y){
    return min(x.a, y.b) < min(y.a, x.b);
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            scanf("%lld %lld", &a[i].a, &a[i].b);
        sort(a + 1, a + 1 + n, cmp);
        for(int i = 1; i <= n; i++){
            sum += a[i].aa;
            f[i] = max(f[i - 1], sum) + a[i].b;
        }
        printf("%lld\n", f[n]);
    }
    return 0;
}