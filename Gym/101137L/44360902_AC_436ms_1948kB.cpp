#include <bits/stdc++.h>

using namespace std;

const int SIZE = 100000 + 5;

int n;
int prob[SIZE], contest[SIZE];
int probCnt[SIZE];
double dp[SIZE];

int main(void) {
    scanf("%d", &n);
    int cntP = 0, cntC = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        char buf[5];
        int tim;
        scanf("%s%d", buf, &tim);
        if (buf[0] == '+') {
            prob[++cntP] = tim;
        } else {
            contest[++cntC] = tim;
        }
    }
    for (int i = 1; i <= n; ++i) {
        int cnt = lower_bound(prob + 1, prob + n + 1, contest[i]) - prob - 1;
        cnt -= i - 1;
        probCnt[i] = cnt;
        // printf("probCnt[%d] = %d\n", i, probCnt[i]);
    }
    dp[n] = contest[n];
    for (int i = n - 1; i; --i) {
        dp[i] = (contest[i] + (probCnt[i] - 1) * dp[i + 1]) / probCnt[i];
        // printf("dp[%d] = %f\n", i, dp[i]);
    }
    for (int i = 1; i <= n; ++i) {
        int id = lower_bound(contest + 1, contest + n + 1, prob[i]) - contest;
        double ans = dp[id] - prob[i];
        printf("%.10f\n", ans);
    }
    return 0;
}