#include <bits/stdc++.h>
using namespace std;

const int N = 2510;

int a[N][N],n,m;
int dp[N][N],dp1[N][N]; //dp[i][j] 表示以[i，j] 为右下／左下单元格能够吃的最多的鱼
int lf[N][N]; // lf[i][j] 表示最多向左延伸多少个格子，使得这些格子中的数都是0)
//int rg[N][N]; // rg[i][j] 表示最多向右延伸多少个格子，使得这些格子中的数都是0）
int up[N][N]; // up[i][j] 表示最多向上延伸多少个格子，使得这些格子中的数都是0）

int main() {
    //freopen("test.txt","r",stdin);
    //freopen("ans.txt","w",stdout);
    scanf("%d%d",&n,&m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d",&a[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!a[i][j]) {
                lf[i][j] = lf[i][j-1] + 1;
                up[i][j] = up[i-1][j] + 1;
                //up1[i][j] = up[i][j];
            }
            else {
                dp[i][j] = min(min(lf[i][j-1], up[i-1][j]), dp[i-1][j-1]) + 1;
                lf[i][j] = 0;
                up[i][j] = 0;
            }
        }
    }
    memset(lf,0,sizeof(lf));
    memset(up,0,sizeof(up));
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            if (a[i][j] == 0) {
                lf[i][j] = lf[i][j+1] + 1;
                up[i][j] = up[i-1][j] + 1;
            }
            else {
                dp[i][j] = min(min(lf[i][j+1], up[i-1][j]), dp[i-1][j+1]) + 1;
                lf[i][j] = 0;
                up[i][j] = 0; 
            }
        }
    }
    int ans = -2333;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            ans = max(ans, max(dp[i][j], dp1[i][j]));
        }
    }
    printf("%d\n",ans);
    return 0;
}