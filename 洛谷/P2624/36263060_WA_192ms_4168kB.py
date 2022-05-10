n = int(input())
a = []
m = 0
ans = 1
for i in range(1, n - 1):
    ans *= i
for i in range(0, n):
    x = int(input())
    a.append(x)
    if x == -1:
        m += 1
    else:
        for i in range(1, x):
            ans //= i
for i in range(0, m - 1):
    ans *= m
print(ans)