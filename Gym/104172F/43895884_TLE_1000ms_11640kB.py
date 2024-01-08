T = int(input())
for t in range(0, T):
    n, k = map(int, input().split())
    k += 1
    s = input()
    pos = [[]] * (k + 1)
    for i in range(1, k):
        x = n * i // k
        if 1 <= x and x <= n:
            pos[i].append(x)
        if 1 <= x - 1 and x - 1 <= n:
            pos[i].append(x - 2)
        if 1 <= x - 2 and x - 2 <= n:
            pos[i].append(x - 2)
        if 1 <= x + 1 and x + 1 <= n:
            pos[i].append(x + 1)
        if 1 <= x + 2 and x + 2 <= n:
            pos[i].append(x + 2)
        if 1 <= x + 3 and x + 3 <= n:
            pos[i].append(x + 3)
    pos[0] = [0]
    pos[k] = [n]
    dp = {}
    dp[0] = [0] * (k + 1)
    for i in range(1, k + 1):
        for r in pos[i]:
            if not r in dp:
                dp[r] = [0] * (k + 1)
            for l in pos[i - 1]:
                if l < r:
                    if dp[r][i]:
                        dp[r][i] = min(dp[r][i], int(s[l:r]) + dp[l][i - 1])
                    else:
                        dp[r][i] = int(s[l:r]) + dp[l][i - 1]
                    # print(i, ':', l, r, dp[r][i], int(s[l:r]), dp[l][i - 1])
    print(dp[n][k])