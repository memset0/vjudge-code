// luogu-judger-enable-o2
#include <bits/stdc++.h>
using namespace std;
int n;
struct node {
    int a, b;
} t[5005];
bool cmp(node a, node b) { return a.a < b.a; }
int main() {
	std::cin >> n;
    for (int i = 1; i <= n; ++i)
		scanf("%d%d", &t[i].a, &t[i].b);
    sort(t + 1, t + 1 + n, cmp);
    int maxa = t[1].a;
    int maxb = t[1].b;
    int ans1 = 0, ans2 = 0;
    for (int i = 2; i <= n; ++i) {
        if (t[i].a <= maxb)
            maxb = max(maxb, t[i].b);
        else {
            ans1 = max(ans1, maxb - maxa);
            ans2 = max(ans2, t[i].a - maxb);
            maxa = t[i].a;
            maxb = t[i].b;
        }
    }
    ans1 = max(ans1, maxb - maxa);
    printf("%d %d", ans1, ans2);
    return 0;
}