#include <bits/stdc++.h>
using namespace std;

const int maxn = 15010;
const int maxm = 40010;
int n, m, t, a[maxm], b[maxn];
struct str_cnt{
    int a, b, c, d;
} cnt[maxm];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
        b[a[i]]++;
    }
    for (int A = 1; A < n; A++) {
        for (int B = A + 1; B < n; B++) {
            for (int C = B + 1; C < n; C++) {
                for (int D = C + 1; D <= n; D++) {
                    if (B - A == 2 * (D - C) && (B - A) * 3 < C - B && (b[A] && b[B] && b[C] && b[D])) {
                        cnt[A].a += b[B] * b[C] * b[D];
                        cnt[B].b += b[A] * b[C] * b[D];
                        cnt[C].c += b[A] * b[B] * b[D];
                        cnt[D].d += b[A] * b[B] * b[C];
                        // cnt[A].a += b[A] * b[B] * b[C] * b[D];
                        // cnt[B].b += b[A] * b[B] * b[C] * b[D];
                        // cnt[C].c += b[A] * b[B] * b[C] * b[D];
                        // cnt[D].d += b[A] * b[B] * b[C] * b[D];
                        // cnt[A].a ++;
                        // cnt[B].b ++;
                        // cnt[C].c ++;
                        // cnt[D].d ++;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        printf("%d %d %d %d\n", cnt[a[i]].a, cnt[a[i]].b, cnt[a[i]].c, cnt[a[i]].d);
    }
    return 0;
}