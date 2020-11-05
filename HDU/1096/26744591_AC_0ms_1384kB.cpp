#include <bits/stdc++.h>
int main() {
#ifdef memset0
    freopen("1.in", "r", stdin);
#endif
    int T, n, x;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        long long s = 0;
        while (n--) {
            scanf("%d", &x);
            s += x;
        }
        printf("%lld\n", s);
        if (T) putchar('\n');
    }
}