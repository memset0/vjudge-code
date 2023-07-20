n, k = map(int, input().split())
k += 1
s = input()
dp = [[0] * (k + 1) for _ in range(n + 1)]
dp[0][0] = 1
for i in range(1, k + 1):
    for r in range(1, n + 1):
        for l in range(0, r):
            dp[r][i] = max(int(s[l:r]) * dp[l][i - 1], dp[r][i])
print(dp[n][k])