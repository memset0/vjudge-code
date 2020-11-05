#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

typedef long long ll;

int Cnt[10];

int F[6][1024], tot[1024];

void Solve() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < 10; i++) Cnt[i] = 0;
    memset(F, 0, sizeof F);
    for(int i = 1; i <= n; i++) {
        char ch[11];
        scanf("%s", ch);
        Cnt[ch[4] - '0']++;
    }
    for(int i = 0; i < 10; i++)
        for(int j = (1 << i); j < (2 << i); j++)
            tot[j] = tot[j - (1 << i)] + Cnt[i];
    memset(F, 63, sizeof F);
    F[0][0] = 0;
    for(int i = 1; i < 6; i++)
        for(int j = 0; j < 1024; j++) {
            int tot = 1023 - j;
            for(int k = tot; ; k = (k - 1) & tot) {
                F[i][k + j] = min(F[i][k + j], max(F[i - 1][j], n - ::tot[k]));
                if(!k) break;
            }
        }
    int ans = n;
    for(int i = 0; i < 1024; i++) ans = min(ans, F[5][i]);
    printf("%d\n", ans);
}

int main() {
    int test;
    scanf("%d", &test);
    while(test--) {
        Solve();
    }
}