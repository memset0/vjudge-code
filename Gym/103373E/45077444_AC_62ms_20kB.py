# p, q = 50, 1
p, q = map(int, input().split())


def sum(n):
    return n * n * (n + 1) * (n + 1) * (2 * n * n + 2 * n - 1) // 12


l = 1
r = 10**4
x = -1
while l <= r:
    mid = (l + r) // 2
    if p <= q * (mid**5):
        x = p * mid - q * sum(mid - 1)
        # print(mid, x)
        r = mid - 1
    else:
        l = mid + 1
print(x)

l = 1
r = 10**20
ans = -1
while l <= r:
    mid = (l + r) // 2
    if q * sum(mid) - p * mid >= (10**99):
        ans = mid
        r = mid - 1
    else:
        l = mid + 1
print(ans)