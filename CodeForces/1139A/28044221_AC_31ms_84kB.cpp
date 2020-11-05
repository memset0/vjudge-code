#include <bits/stdc++.h>
int n, ans;
char s[66666];
int main() {
    scanf("%d%s", &n, s+1);
    for(int i = 1; i <= n; i++)
        if (!((s[i]-'0')&1))
            ans += i;
    printf("%d\n", ans);
}