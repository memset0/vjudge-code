k, n = map(int, raw_input().split())
a, b, c = 0, 1, k
s = {0}
for i in range(0, n):
    while True:
        ta, tb, tc = a, b, c
        a, b, c = tb, tc, (tb+tc)*k-ta
        if not (a in s or b in s or c in s):
            break
        a, b, c = ta, tb, (ta+tb)*k-tc
        if not (a in s or b in s or c in s):
            break
        a, b, c = ta, tc, (ta+tc)*k-tb
        if not (a in s or b in s or c in s):
            break
    s.update([a, b, c])
    print a, b, c
