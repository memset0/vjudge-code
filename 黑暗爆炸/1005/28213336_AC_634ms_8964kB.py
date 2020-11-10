def fac(x):
    ans = 1
    for i in range(1, x + 1):
        ans *= i
    return ans
def choose(n, m):
    return fac(n) // fac(m) // fac(n - m)

n = int(input()); a = []; cnt = 0; lst = n - 2
ans = fac(n - 2)
for i in range(0, n):
    x = int(input()); a.append(x)
    if x != -1:
        lst -= x - 1
        for i in range(1, x):
            ans //= i
    else:
        cnt += 1
ans //= fac(lst)
for i in range(0, lst):
    ans *= cnt
print(ans)