// luogu-judger-enable-o2
#include <bits/stdc++.h>
int n, x, y, s;
int main() {
    scanf("%d%d", &n, &y);
    for (int i = 2; i <= n; i++) {
        x = y, scanf("%d", &x);
        s += abs(y - x);
    }
    s /= 2, printf("%d", s);
}