#include <bits/stdc++.h>

const int N = 2e5 + 10;
int n, a[N];
long long ans=0;

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    int t = a[n];
    for (int i = n; i >= 1; --i) {
        t = t < a[i] ? t : a[i];
        ans += t--;
        if (t<=0) break;
    }
    std::cout << ans << std::endl;
    return 0;
}