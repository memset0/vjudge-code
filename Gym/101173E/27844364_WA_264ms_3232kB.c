k, n = map(int, raw_input().split())
a, b, c = 0, 1, k
s = {0}
for i in range(0, n):
    while True:
        a, b, c = b, c, (b+c)*k-a
        if not (a in s or b in s or c in s):
            break
    s.update([a, b, c])
    print a, b, c
