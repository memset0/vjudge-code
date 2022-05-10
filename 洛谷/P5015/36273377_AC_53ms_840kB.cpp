// luogu-judger-enable-o2
#include <bits/stdc++.h>
int main() {
    int ans = 0, c;
    while ((c = getchar()) != EOF)
        if (isdigit(c) || isalpha(c)) ++ans;
    printf("%d\n", ans);
    return 0;
}