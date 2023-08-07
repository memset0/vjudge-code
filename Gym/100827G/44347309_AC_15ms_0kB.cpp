#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100 + 5;
int N, a[MAX_N], pos[MAX_N];

void solve() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i ++) {
        scanf("%d", a + i);
        pos[a[i]] = i;
    }
    int x = pos[1];
    int l, r, l2, r2;
    for (l = x; l > 1 && a[l - 1] > a[l]; l --);
    for (r = x; r < N && a[r + 1] > a[r]; r ++);
    for (l2 = l; l2 > 1 && a[l2 - 1] < a[l2]; l2 --);
    for (r2 = r; r2 < N && a[r2 + 1] < a[r2]; r2 ++);
    if (x == 1) {
        if (r - x < 2) {
            int r_ = r2 - r;
            if (N - r_ & 1) printf("Alice\n");
            else printf("Bob\n");
        }else {
            if (N & 1) printf("Alice\n");
            else printf("Bob\n");
        }
    }else if (x == N) {
        if (x - l < 2) {
            int r_ = l - l2;
            if (N - r_ & 1) printf("Alice\n");
            else printf("Bob\n");
        }else {
            if (N & 1) printf("Alice\n");
            else printf("Bob\n");
        }
    }else if (x - l < 2 && r - x < 2) {
        int l_ = l - l2, r_ = r2 - r;
        if (N - l_ & 1 || N - r_ & 1) printf("Alice\n");
        else printf("Bob\n");
    }else {
        if (N & 1) printf("Alice\n");
        else printf("Bob\n");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T --) solve();
    return 0;
}