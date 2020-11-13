k, n = map(int, raw_input().split())
s = {0}
x = [(0, 1, k)]
y = []
p = 0
for i in range(0, n):
    while True:
        while p < len(x):
            a, b, c = x[p]
            if not (a in s or b in s or c in s) and a > 0 and b > 0 and c > 0:
                break
            p += 1
        if p < len(x):
            a, b, c = x[p]
            s.update([a, b, c])
            print a, b, c
            break
        else:
            x, y = [], x
            for q in range(0, len(y)):
                a, b, c = y[q]
                if (b+c)*k > a:
                    x.append((b, c, (b+c)*k-a))
                if (a+c)*k > b:
                    x.append((a, c, (a+c)*k-b))
                if (a+b)*k > c:
                    x.append((a, b, (a+b)*k-c))
            p = 0
# vj hello    dfsdfsff